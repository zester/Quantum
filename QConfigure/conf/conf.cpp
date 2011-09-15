// For license information, see the COPYING file in the qconf base directory.

#include<stdio.h>
#include<stdlib.h>
#include<qstring.h>
#include<qdict.h>
#include<qptrlist.h>
#include<qfileinfo.h>
#include<qfile.h>
#include<qdir.h>
#include<qstringlist.h>
#include<qobject.h>

class MocTestObject : public QObject
{
	Q_OBJECT
public:
	MocTestObject() {}
};

class Conf;

class ConfObj
{
public:
	ConfObj(Conf *c);
	virtual ~ConfObj();

	virtual QString name() const=0;
	virtual QString shortname() const=0;
	virtual QString checkString() const;
	virtual QString resultString() const;
	virtual bool exec()=0;

	Conf *conf;
	bool required;
	bool disabled;
};

typedef QPtrList<ConfObj> ConfObjList;
typedef QPtrListIterator<ConfObj> ConfObjListIt;

class Conf
{
public:
	Conf() : vars(17)
	{
		list.setAutoDelete(true);
		vars.setAutoDelete(true);

		vars.insert("QMAKE_INCDIR_X11", new QString(X11_INC));
		vars.insert("QMAKE_LIBDIR_X11", new QString(X11_LIBDIR));
		vars.insert("QMAKE_LIBS_X11",   new QString(X11_LIB));
		vars.insert("QMAKE_CC",         new QString(CC));
		vars.insert("QMAKE_CXX",        new QString(CXX));

		do_debug = false;
		done_debug = false;
	}

	~Conf()
	{
	}

	void added(ConfObj *o)
	{
		list.append(o);
	}

	QString getenv(const QString &var)
	{
		char *p = ::getenv(var.latin1());
		if(!p)
			return QString::null;
		return QString(p);
	}

	void debug(const QString &s)
	{
		if(do_debug) {
			if(!done_debug)
				printf("\n");
			done_debug = true;
			printf(" * %s\n", s.latin1());
		}
	}

	bool exec()
	{
		if(getenv("QC_VERBOSE") == "Y")
			do_debug = true;

		ConfObjListIt it(list);
		for(ConfObj *o; (o = it.current()); ++it) {
			// if this was a disabled-by-default option, check if it was enabled
			if(o->disabled) {
				QString v = QString("QC_ENABLE_") + o->shortname();
				if(getenv(v) != "Y")
					continue;
			}
			// and the opposite?
			else {
				QString v = QString("QC_DISABLE_") + o->shortname();
				if(getenv(v) == "Y")
					continue;
			}

			QString check = o->checkString();
			if(check.isEmpty())
				check = QString("Checking for %1 ...").arg(o->name());
			printf("%s", check.latin1());
			fflush(stdout);

			done_debug = false;
			bool ok = o->exec();

			QString result = o->resultString();
			if(result.isEmpty()) {
				if(ok)
					result = "yes";
				else
					result = "no";
			}
			if(done_debug)
				printf(" -> %s\n", result.latin1());
			else
				printf(" %s\n", result.latin1());

			if(!ok && o->required) {
				printf("\nError: need %s!\n", o->name().latin1());
				return false;
			}
		}
		return true;
	}

	const QString & qvar(const QString &s)
	{
		QString *p = vars.find(s);
		if(p)
			return *p;
		else
			return blank;
	}

	QString expandIncludes(const QString &inc)
	{
		return QString("-I") + inc;
	}

	QString expandLibs(const QString &lib)
	{
		return QString("-L") + lib;
	}

	int doCommand(const QString &s)
	{
		debug(QString("[%1]").arg(s));
		QString fullcmd;
		if(do_debug)
			fullcmd = s;
		else
			fullcmd = s + " 1>/dev/null 2>/dev/null";
		int r = system(fullcmd.latin1());
		debug(QString("returned: %1").arg(r));
		return r;
	}

	bool doCompileAndLink(const QString &filedata, const QString &flags, int *retcode=0)
	{
		QDir dir(".");
		QString fname = "atest.c";
		QString out = "atest";
		QFile f(fname);
		QCString cs = filedata.latin1();
		if(!f.open(IO_WriteOnly | IO_Truncate)) {
			debug("unable to open atest.c for writing");
			return false;
		}
		if(f.writeBlock(cs.data(), cs.length()) == -1) {
			debug("error writing to atest.c");
			return false;
		}
		f.close();

		debug(QString("Wrote atest.c:\n%1").arg(filedata));

		QString str = qvar("QMAKE_CXX") + ' ' + fname + " -o " + out;
		if(!flags.isEmpty()) {
			str += ' ';
			str += flags;
		}

		int r = doCommand(str);
		if(r == 0 && retcode)
			*retcode = doCommand(QString("./") + out);
		dir.remove(fname);
		dir.remove(out);
		if(r != 0)
			return false;
		return true;
	}

	bool checkHeader(const QString &path, const QString &h)
	{
		QFileInfo fi(path + '/' + h);
		if(fi.exists())
			return true;
		return false;
	}

	bool findHeader(const QString &h, const QStringList &ext, QString *inc)
	{
		if(checkHeader("/usr/include", h)) {
			*inc = "";
			return true;
		}
		QStringList dirs;
		dirs += "/usr/local/include";
		dirs += ext;
		for(QStringList::ConstIterator it = dirs.begin(); it != dirs.end(); ++it) {
			if(checkHeader(*it, h)) {
				*inc = *it;
				return true;
			}
		}
		return false;
	}

	bool checkLibrary(const QString &path, const QString &name)
	{
		QString str =
			"int main()\n"
			"{\n"
			"    return 0;\n"
			"}\n";

		QString extra;
		if(!path.isEmpty())
			extra += QString("-L") + path + ' ';
		extra += QString("-l") + name;
		if(!doCompileAndLink(str, extra))
			return false;
		return true;
	}

	bool findLibrary(const QString &name, QString *lib)
	{
		if(checkLibrary("", name)) {
			*lib = "";
			return true;
		}
		if(checkLibrary("/usr/local/lib", name)) {
			*lib = "/usr/local/lib";
			return true;
		}
		return false;
	}

	void addDefine(const QString &str)
	{
		if(DEFINES.isEmpty())
			DEFINES = str;
		else
			DEFINES += QString(" ") + str;
		debug(QString("DEFINES += %1").arg(str));
	}

	void addLib(const QString &str)
	{
		if(LIBS.isEmpty())
			LIBS = str;
		else
			LIBS += QString(" ") + str;
		debug(QString("LIBS += %1").arg(str));
	}

	void addIncludePath(const QString &str)
	{
		if(INCLUDEPATH.isEmpty())
			INCLUDEPATH = str;
		else
			INCLUDEPATH += QString(" ") + str;
		debug(QString("INCLUDEPATH += %1").arg(str));
	}

	void addExtra(const QString &str)
	{
		extra += str + '\n';
		debug(QString("extra += %1").arg(str));
	}

	QString DEFINES;
	QString INCLUDEPATH;
	QString LIBS;
	QString extra;

private:
	ConfObjList list;
	QDict<QString> vars;
	QString blank;
	bool do_debug, done_debug;
};

ConfObj::ConfObj(Conf *c)
{
	conf = c;
	conf->added(this);
	required = false;
	disabled = false;
}

ConfObj::~ConfObj()
{
}

QString ConfObj::checkString() const
{
	return QString();
}

QString ConfObj::resultString() const
{
	return QString();
}

#include"modules.cpp"

//----------------------------------------------------------------------------
// main
//----------------------------------------------------------------------------
int main()
{
	Conf *conf = new Conf;
	ConfObj *o;
	o = 0;
#include"modules_new.cpp"

	printf("ok\n");
	bool success = false;
	if(conf->exec()) {
		QFile f("conf.pri");
		if(!f.open(IO_WriteOnly | IO_Truncate)) {
			printf("Error writing %s\n", f.name().latin1());
			return 1;
		}

		QString str;
		str += "# qconf\n";
		str += "QT_PATH_PLUGINS = " + QString(qInstallPathPlugins()) + '\n';
		if(!conf->DEFINES.isEmpty())
			str += "DEFINES += " + conf->DEFINES + '\n';
		if(!conf->INCLUDEPATH.isEmpty())
			str += "INCLUDEPATH += " + conf->INCLUDEPATH + '\n';
		if(!conf->LIBS.isEmpty())
			str += "LIBS += " + conf->LIBS + '\n';
		if(!conf->extra.isEmpty())
			str += conf->extra;
		str += '\n';

		char *p = getenv("BINDIR");
		if(p) {
			str += QString("target.path = ") + p + '\n';
			str += "INSTALLS += target\n";
		}

		QCString cs = str.latin1();
		f.writeBlock(cs.data(), cs.length());
		f.close();
		success = true;
	}
	delete conf;

	if(success)
		return 0;
	else
		return 1;
}

#include"conf.moc"

