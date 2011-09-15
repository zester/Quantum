// For license information, see the COPYING file in the qconf base directory.

#include "conf4.h"

#include <stdio.h>
#include <stdlib.h>

class MocTestObject : public QObject
{
	Q_OBJECT
public:
	MocTestObject() {}
};

QString qc_getenv(const QString &var)
{
	char *p = ::getenv(var.toLatin1().data());
	if(!p)
		return QString();
	return QString(p);
}

QStringList qc_pathlist()
{
	QStringList list;
	QString path = qc_getenv("PATH");
	if(!path.isEmpty())
		list = path.split(':', QString::SkipEmptyParts);
	return list;
}

QString qc_findprogram(const QString &prog)
{
	QString out;
	QStringList list = qc_pathlist();
	for(int n = 0; n < list.count(); ++n)
	{
		QFileInfo fi(list[n] + '/' + prog);
		if(fi.exists() && fi.isExecutable())
		{
			out = fi.filePath();
			break;
		}
	}
	return out;
}

QString qc_findself(const QString &argv0)
{
	if(argv0.contains('/'))
		return argv0;
	else
		return qc_findprogram(argv0);
}

int qc_runcommand(const QString &command, QByteArray *out, bool showOutput)
{
	QString fullcmd = command;
	if(!showOutput)
		fullcmd += " 2>/dev/null";
	FILE *f = popen(fullcmd.toLatin1().data(), "r");
	if(!f)
		return -1;
	if(out)
		out->clear();
	while(1)
	{
		char c = (char)fgetc(f);
		if(feof(f))
			break;
		if(out)
			out->append(c);
		if(showOutput)
			fputc(c, stdout);
	}
	int ret = pclose(f);
	if(ret == -1)
		return -1;
	return ret;
}

int qc_runprogram(const QString &prog, const QStringList &args, QByteArray *out, bool showOutput)
{
	QString fullcmd = prog;
	QString argstr = args.join(" ");
	if(!argstr.isEmpty())
		fullcmd += QString(" ") + argstr;
	return qc_runcommand(fullcmd, out, showOutput);

	// TODO: use QProcess once it is fixed
	/*
	QProcess process;
	if(showOutput)
		process.setReadChannelMode(ForwardedChannels);
	process.start(prog, args);
	process.waitForFinished(-1);
	return process.exitCode();
	*/
}

bool qc_removedir(const QString &dirPath)
{
	QDir dir(dirPath);
	if(!dir.exists())
		return false;
	QStringList list = dir.entryList();
	foreach(QString s, list)
	{
		if(s == "." || s == "..")
			continue;
		QFileInfo fi(dir.filePath(s));
		if(fi.isDir())
		{
			if(!qc_removedir(fi.filePath()))
				return false;
		}
		else
		{
			if(!dir.remove(s))
				return false;
		}
	}
	QString dirName = dir.dirName();
	if(!dir.cdUp())
		return false;
	if(!dir.rmdir(dirName))
		return false;
	return true;
}

void qc_splitcflags(const QString &cflags, QStringList *incs, QStringList *otherflags)
{
	incs->clear();
	otherflags->clear();

	QStringList cflagsList = cflags.split(" ");
	for(int n = 0; n < cflagsList.count(); ++n)
	{
		QString str = cflagsList[n];
		if(str.startsWith("-I"))
		{
			// we want everything except the leading "-I"
			incs->append(str.remove(0, 2));
		}
		else
		{
			// we want whatever is left
			otherflags->append(str);
		}
	}
}

QString qc_escapeArg(const QString &str)
{
	QString out;
	for(int n = 0; n < (int)str.length(); ++n) {
		if(str[n] == '-')
			out += '_';
		else
			out += str[n];
	}
	return out;
}

//----------------------------------------------------------------------------
// ConfObj
//----------------------------------------------------------------------------
ConfObj::ConfObj(Conf *c)
{
	conf = c;
	conf->added(this);
	required = false;
	disabled = false;
	success = false;
}

ConfObj::~ConfObj()
{
}

QString ConfObj::checkString() const
{
	return QString("Checking for %1 ...").arg(name());
}

QString ConfObj::resultString() const
{
	if(success)
		return "yes";
	else
		return "no";
}

//----------------------------------------------------------------------------
// qc_internal_pkgconfig
//----------------------------------------------------------------------------
class qc_internal_pkgconfig : public ConfObj
{
public:
	QString pkgname, desc;
	VersionMode mode;
	QString req_ver;

        qc_internal_pkgconfig(Conf *c, const QString &_name, const QString &_desc, VersionMode _mode, const QString &_req_ver) : ConfObj(c)
	{
		pkgname = _name;
		desc = _desc;
		mode = _mode;
		req_ver = _req_ver;
	}

	QString name() const { return desc; }
	QString shortname() const { return pkgname; }

	bool exec()
	{
		QStringList incs;
		QString version, libs, other;
		if(!conf->findPkgConfig(pkgname, mode, req_ver, &version, &incs, &libs, &other))
			return false;

		for(int n = 0; n < incs.count(); ++n)
			conf->addIncludePath(incs[n]);
		if(!libs.isEmpty())
			conf->addLib(libs);
		//if(!other.isEmpty())
		//	conf->addExtra(QString("QMAKE_CFLAGS += %1\n").arg(other));
		return true;
	}
};

//----------------------------------------------------------------------------
// Conf
//----------------------------------------------------------------------------
Conf::Conf()
{
	// TODO: no more vars?
	//vars.insert("QMAKE_INCDIR_X11", new QString(X11_INC));
	//vars.insert("QMAKE_LIBDIR_X11", new QString(X11_LIBDIR));
	//vars.insert("QMAKE_LIBS_X11",   new QString(X11_LIB));
	//vars.insert("QMAKE_CC", CC);

	debug_enabled = false;
}

Conf::~Conf()
{
	qDeleteAll(list);
}

void Conf::added(ConfObj *o)
{
	list.append(o);
}

QString Conf::getenv(const QString &var)
{
	return qc_getenv(var);
}

void Conf::debug(const QString &s)
{
	if(debug_enabled)
	{
		if(first_debug)
			printf("\n");
		first_debug = false;
		printf(" * %s\n", qPrintable(s));
	}
}

bool Conf::exec()
{
	for(int n = 0; n < list.count(); ++n)
	{
		ConfObj *o = list[n];

		// if this was a disabled-by-default option, check if it was enabled
		if(o->disabled)
		{
			QString v = QString("QC_ENABLE_") + qc_escapeArg(o->shortname());
			if(getenv(v) != "Y")
				continue;
		}
		// and the opposite?
		else
		{
			QString v = QString("QC_DISABLE_") + qc_escapeArg(o->shortname());
			if(getenv(v) == "Y")
				continue;
		}

		bool output = true;
		QString check = o->checkString();
		if(check.isEmpty())
			output = false;

		if(output)
		{
			printf("%s", check.toLatin1().data());
			fflush(stdout);
		}

		first_debug = true;
		bool ok = o->exec();
		o->success = ok;

		if(output)
		{
			QString result = o->resultString();
			if(!first_debug)
				printf(" -> %s\n", result.toLatin1().data());
			else
				printf(" %s\n", result.toLatin1().data());
		}

		if(!ok && o->required)
		{
			printf("\nError: need %s!\n", o->name().toLatin1().data());
			return false;
		}
	}
	return true;
}

QString Conf::qvar(const QString &s)
{
	return vars.value(s);
}

QString Conf::expandIncludes(const QString &inc)
{
	return QString("-I") + inc;
}

QString Conf::expandLibs(const QString &lib)
{
	return QString("-L") + lib;
}

int Conf::doCommand(const QString &s, QByteArray *out)
{
	debug(QString("[%1]").arg(s));
	int r = qc_runcommand(s, out, debug_enabled);
	debug(QString("returned: %1").arg(r));
	return r;
}

int Conf::doCommand(const QString &prog, const QStringList &args, QByteArray *out)
{
	QString fullcmd = prog;
	QString argstr = args.join(" ");
	if(!argstr.isEmpty())
		fullcmd += QString(" ") + argstr;
	debug(QString("[%1]").arg(fullcmd));
	int r = qc_runprogram(prog, args, out, debug_enabled);
	debug(QString("returned: %1").arg(r));
	return r;
}

bool Conf::doCompileAndLink(const QString &filedata, const QStringList &incs, const QString &libs, const QString &proextra, int *retcode)
{
	QDir tmp(".qconftemp");
	if(!tmp.mkdir("atest"))
	{
		debug("unable to create atest dir");
		return false;
	}
	QDir dir(tmp.filePath("atest"));
	if(!dir.exists())
	{
		debug("atest dir does not exist");
		return false;
	}

	QString fname = dir.filePath("atest.cpp");
	QString out = "atest";
	QFile f(fname);
	if(!f.open(QFile::WriteOnly | QFile::Truncate))
	{
		debug("unable to open atest.cpp for writing");
		return false;
	}
	if(f.write(filedata.toLatin1()) == -1)
	{
		debug("error writing to atest.cpp");
		return false;
	}
	f.close();

	debug(QString("Wrote atest.cpp:\n%1").arg(filedata));

	QString pro = QString(
		"CONFIG  += console\n"
		"CONFIG  -= qt app_bundle\n"
		"SOURCES += atest.cpp\n");
	QString inc = incs.join(" ");
	if(!inc.isEmpty())
		pro += "INCLUDEPATH += " + inc + '\n';
	if(!libs.isEmpty())
		pro += "LIBS += " + libs + '\n';
	pro += proextra;

	fname = dir.filePath("atest.pro");
	f.setFileName(fname);
	if(!f.open(QFile::WriteOnly | QFile::Truncate))
	{
		debug("unable to open atest.pro for writing");
		return false;
	}
	if(f.write(pro.toLatin1()) == -1)
	{
		debug("error writing to atest.pro");
		return false;
	}
	f.close();

	debug(QString("Wrote atest.pro:\n%1").arg(pro));

	QString oldpath = QDir::currentPath();
	QDir::setCurrent(dir.path());

	bool ok = false;
	int r = doCommand(qmake_path, QStringList() << "atest.pro");
	if(r == 0)
	{
		r = doCommand(maketool, QStringList());
		if(r == 0)
		{
			ok = true;
			if(retcode)
				*retcode = doCommand(QString("./") + out, QStringList());
		}
		r = doCommand(maketool, QStringList() << "distclean");
		if(r != 0)
			debug("error during atest distclean");
	}

	QDir::setCurrent(oldpath);

	// cleanup
	//dir.remove("atest.pro");
	//dir.remove("atest.cpp");
	//tmp.rmdir("atest");

	// remove whole dir since distclean doesn't always work
	qc_removedir(tmp.filePath("atest"));

	if(!ok)
		return false;
	return true;
}

bool Conf::checkHeader(const QString &path, const QString &h)
{
	QFileInfo fi(path + '/' + h);
	if(fi.exists())
		return true;
	return false;
}

bool Conf::findHeader(const QString &h, const QStringList &ext, QString *inc)
{
	if(checkHeader("/usr/include", h))
	{
		*inc = "";
		return true;
	}
	QStringList dirs;
	dirs += "/usr/local/include";
	dirs += ext;
	for(QStringList::ConstIterator it = dirs.begin(); it != dirs.end(); ++it)
	{
		if(checkHeader(*it, h))
		{
			*inc = *it;
			return true;
		}
	}
	return false;
}

bool Conf::checkLibrary(const QString &path, const QString &name)
{
	QString str =
		//"#include <stdio.h>\n"
		"int main()\n"
		"{\n"
		//"    printf(\"library checker running\\\\n\");\n"
		"    return 0;\n"
		"}\n";

	QString libs;
	if(!path.isEmpty())
		libs += QString("-L") + path + ' ';
	libs += QString("-l") + name;
	if(!doCompileAndLink(str, QStringList(), libs, QString()))
		return false;
	return true;
}

bool Conf::findLibrary(const QString &name, QString *lib)
{
	if(checkLibrary("", name))
	{
		*lib = "";
		return true;
	}
	if(checkLibrary("/usr/local/lib", name))
	{
		*lib = "/usr/local/lib";
		return true;
	}
	return false;
}

QString Conf::findProgram(const QString &prog)
{
	return qc_findprogram(prog);
}

bool Conf::findSimpleLibrary(const QString &incvar, const QString &libvar, const QString &incname, const QString &libname, QString *incpath, QString *libs)
{
	QString inc, lib;
	QString s;

	s = getenv(incvar);
	if(!s.isEmpty()) {
		if(!checkHeader(s, incname))
			return false;
		inc = s;
	}
	else {
		if(!findHeader(incname, QStringList(), &s))
			return false;
		inc = s;
	}

	s = getenv(libvar);
	if(!s.isEmpty()) {
		if(!checkLibrary(s, libname))
			return false;
		lib = s;
	}
	else {
		if(!findLibrary(libname, &s))
			return false;
		lib = s;
	}

	QString lib_out;
	if(!lib.isEmpty())
		lib_out += QString("-L") + s;
	lib_out += QString("-l") + libname;

	*incpath = inc;
	*libs = lib_out;
	return true;
}

bool Conf::findFooConfig(const QString &path, QString *version, QStringList *incs, QString *libs, QString *otherflags)
{
	QStringList args;
	QByteArray out;
	int ret;

	args += "--version";
	ret = doCommand(path, args, &out);
	if(ret != 0)
		return false;

	QString version_out = QString::fromLatin1(out).trimmed();

	args.clear();
	args += "--libs";
	ret = doCommand(path, args, &out);
	if(ret != 0)
		return false;

	QString libs_out = QString::fromLatin1(out).trimmed();

	args.clear();
	args += "--cflags";
	ret = doCommand(path, args, &out);
	if(ret != 0)
		return false;

	QString cflags = QString::fromLatin1(out).trimmed();

	QStringList incs_out, otherflags_out;
	qc_splitcflags(cflags, &incs_out, &otherflags_out);

	*version = version_out;
	*incs = incs_out;
	*libs = libs_out;
	*otherflags = otherflags_out.join(" ");
	return true;
}

bool Conf::findPkgConfig(const QString &name, VersionMode mode, const QString &req_version, QString *version, QStringList *incs, QString *libs, QString *otherflags)
{
	QStringList args;
	QByteArray out;
	int ret;

	args += name;
	args += "--exists";
	ret = doCommand("pkg-config", args, &out);
	if(ret != 0)
		return false;

	if(mode != VersionAny)
	{
		args.clear();
		args += name;
		if(mode == VersionMin)
			args += QString("--atleast-version=%1").arg(req_version);
		else if(mode == VersionMax)
			args += QString("--max-version=%1").arg(req_version);
		else
			args += QString("--exact-version=%1").arg(req_version);
		ret = doCommand("pkg-config", args, &out);
		if(ret != 0)
			return false;
	}

	args.clear();
	args += name;
	args += "--modversion";
	ret = doCommand("pkg-config", args, &out);
	if(ret != 0)
		return false;

	QString version_out = QString::fromLatin1(out).trimmed();

	args.clear();
	args += name;
	args += "--libs";
	ret = doCommand("pkg-config", args, &out);
	if(ret != 0)
		return false;

	QString libs_out = QString::fromLatin1(out).trimmed();

	args.clear();
	args += name;
	args += "--cflags";
	ret = doCommand("pkg-config", args, &out);
	if(ret != 0)
		return false;

	QString cflags = QString::fromLatin1(out).trimmed();

	QStringList incs_out, otherflags_out;
	qc_splitcflags(cflags, &incs_out, &otherflags_out);

	*version = version_out;
	*incs = incs_out;
	*libs = libs_out;
	*otherflags = otherflags_out.join(" ");
	return true;
}

void Conf::addDefine(const QString &str)
{
	if(DEFINES.isEmpty())
		DEFINES = str;
	else
		DEFINES += QString(" ") + str;
	debug(QString("DEFINES += %1").arg(str));
}

void Conf::addLib(const QString &str)
{
	if(LIBS.isEmpty())
		LIBS = str;
	else
		LIBS += QString(" ") + str;
	debug(QString("LIBS += %1").arg(str));
}

void Conf::addIncludePath(const QString &str)
{
	if(INCLUDEPATH.isEmpty())
		INCLUDEPATH = str;
	else
		INCLUDEPATH += QString(" ") + str;
	debug(QString("INCLUDEPATH += %1").arg(str));
}

void Conf::addExtra(const QString &str)
{
	extra += str + '\n';
	debug(QString("extra += %1").arg(str));
}

//----------------------------------------------------------------------------
// main
//----------------------------------------------------------------------------
#include "conf4.moc"

#ifdef HAVE_MODULES
# include"modules.cpp"
#endif

int main()
{
	Conf *conf = new Conf;
	ConfObj *o;
	o = 0;
#ifdef HAVE_MODULES
# include"modules_new.cpp"
#endif

	conf->debug_enabled = (qc_getenv("QC_VERBOSE") == "Y") ? true: false;
	if(conf->debug_enabled)
		printf(" -> ok\n");
	else
		printf("ok\n");

	QString confCommand = qc_getenv("QC_COMMAND");
	QString proName = qc_getenv("QC_PROFILE");
	conf->qmake_path = qc_getenv("QC_QMAKE");
	conf->maketool = qc_getenv("QC_MAKETOOL");

	if(conf->debug_enabled)
		printf("conf command: [%s]\n", qPrintable(confCommand));

	QString confPath = qc_findself(confCommand);
	if(confPath.isEmpty())
	{
		printf("Error: cannot find myself; rerun with an absolute path\n");
		return 1;
	}

	QString srcdir = QFileInfo(confPath).absolutePath();
	QString builddir = QDir::current().absolutePath();
	QString proPath = QDir(srcdir).filePath(proName);

	if(conf->debug_enabled)
	{
		printf("conf path:    [%s]\n", qPrintable(confPath));
		printf("srcdir:       [%s]\n", qPrintable(srcdir));
		printf("builddir:     [%s]\n", qPrintable(builddir));
		printf("profile:      [%s]\n", qPrintable(proPath));
		printf("qmake path:   [%s]\n", qPrintable(conf->qmake_path));
		printf("make tool:    [%s]\n", qPrintable(conf->maketool));
		printf("\n");
	}

	bool success = false;
	if(conf->exec())
	{
		QFile f("conf.pri");
		if(!f.open(QFile::WriteOnly | QFile::Truncate))
		{
			printf("Error writing %s\n", qPrintable(f.fileName()));
			return 1;
		}

		QString str;
		str += "# qconf\n\n";

		QString var;
		var = qc_getenv("PREFIX");
		if(!var.isEmpty())
			str += QString("PREFIX = %1\n").arg(var);
		var = qc_getenv("BINDIR");
		if(!var.isEmpty())
			str += QString("BINDIR = %1\n").arg(var);
		var = qc_getenv("INCDIR");
		if(!var.isEmpty())
			str += QString("INCDIR = %1\n").arg(var);
		var = qc_getenv("LIBDIR");
		if(!var.isEmpty())
			str += QString("LIBDIR = %1\n").arg(var);
		var = qc_getenv("DATADIR");
		if(!var.isEmpty())
			str += QString("DATADIR = %1\n").arg(var);
		str += '\n';

		if(qc_getenv("QC_STATIC") == "Y")
			str += "CONFIG += staticlib\n";

		// TODO: don't need this?
		//str += "QT_PATH_PLUGINS = " + QString(qInstallPathPlugins()) + '\n';

		if(!conf->DEFINES.isEmpty())
			str += "DEFINES += " + conf->DEFINES + '\n';
		if(!conf->INCLUDEPATH.isEmpty())
			str += "INCLUDEPATH += " + conf->INCLUDEPATH + '\n';
		if(!conf->LIBS.isEmpty())
			str += "LIBS += " + conf->LIBS + '\n';
		if(!conf->extra.isEmpty())
			str += conf->extra;
		str += '\n';

		QByteArray cs = str.toLatin1();
		f.write(cs);
		f.close();
		success = true;
	}
	QString qmake_path = conf->qmake_path;
	delete conf;

	if(!success)
		return 1;

	// run qmake on the project file
	int ret = qc_runprogram(qmake_path, QStringList() << proPath, 0, true);
	if(ret != 0)
		return 1;

	return 0;
}
