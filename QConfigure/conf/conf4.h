// For license information, see the COPYING file in the qconf base directory.

#ifndef QC_CONF4_H
#define QC_CONF4_H

#include <QtCore>

class Conf;

enum VersionMode { VersionMin, VersionExact, VersionMax, VersionAny };

// ConfObj
//
// Subclass ConfObj to create a new configuration module.
class ConfObj
{
public:
	Conf *conf;
	bool required;
	bool disabled;
	bool success;

	ConfObj(Conf *c);
	virtual ~ConfObj();

	// long or descriptive name of what is being checked/performed
	// example: "KDE >= 3.3"
	virtual QString name() const = 0;

	// short name
	// example: "kde"
	virtual QString shortname() const = 0;

	// string to display during check
	// default: "Checking for [name] ..."
	virtual QString checkString() const;

	// string to display after check
	// default: "yes" or "no", based on result of exec()
	virtual QString resultString() const;

	// this is where the checking code goes
	virtual bool exec() = 0;
};

// Conf
//
// Interact with this class from your ConfObj to perform detection
// operations and to output configuration parameters.
class Conf
{
public:
	bool debug_enabled;
	QString qmake_path;
	QString maketool;

	QString DEFINES;
	QString INCLUDEPATH;
	QString LIBS;
	QString extra;

	QList<ConfObj*> list;
	QMap<QString,QString> vars;

	Conf();
	~Conf();

	QString getenv(const QString &var);
	QString qvar(const QString &s);

	bool exec();

	void debug(const QString &s);

	QString expandIncludes(const QString &inc);
	QString expandLibs(const QString &lib);

	int doCommand(const QString &s, QByteArray *out = 0);
	int doCommand(const QString &prog, const QStringList &args, QByteArray *out = 0);

	bool doCompileAndLink(const QString &filedata, const QStringList &incs, const QString &libs, const QString &proextra, int *retcode = 0);
	bool checkHeader(const QString &path, const QString &h);
	bool findHeader(const QString &h, const QStringList &ext, QString *inc);
	bool checkLibrary(const QString &path, const QString &name);
	bool findLibrary(const QString &name, QString *lib);
	QString findProgram(const QString &prog);
	bool findSimpleLibrary(const QString &incvar, const QString &libvar, const QString &incname, const QString &libname, QString *incpath, QString *libs);
	bool findFooConfig(const QString &path, QString *version, QStringList *incs, QString *libs, QString *otherflags);
	bool findPkgConfig(const QString &name, VersionMode mode, const QString &req_version, QString *version, QStringList *incs, QString *libs, QString *otherflags);

	void addDefine(const QString &str);
	void addLib(const QString &str);
	void addIncludePath(const QString &str);
	void addExtra(const QString &str);

private:
	bool first_debug;

	friend class ConfObj;
	void added(ConfObj *o);
};

#endif
