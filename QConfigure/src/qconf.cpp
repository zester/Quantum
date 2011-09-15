/*
 * qconf.cpp - main qconf source
 * Copyright (C) 2003-2007  Justin Karneges
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <QtCore>
#include <QtXml>

// for chmod
#include <sys/types.h>
#include <sys/stat.h>

#include "stringhelp.h"

#define VERSION "1.4"

#define CONF_USAGE_SPACE 4
#define CONF_WRAP        78

bool looksLikeInPlace(const QString &path)
{
	QFileInfo confinfo(path + "/conf");
	QFileInfo modulesinfo(path + "/modules");
	if(confinfo.exists() && confinfo.isDir() && modulesinfo.exists() && modulesinfo.isDir())
		return true;
	return false;
}

QString escapeFile(const QString &str)
{
	QString out;
	for(int n = 0; n < (int)str.length(); ++n) {
		if(str[n] == '$' || str[n] == '`')
			out += '\\';
		out += str[n];
	}
	return out;
}

QString escapeArg(const QString &str)
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

QString c_escape(const QString &in)
{
	QString out;
	for(int n = 0; n < in.length(); ++n)
	{
		/*if(in[n] == '\\')
			out += "\\\\";
		else*/ if(in[n] == '\"')
			out += "\\\"";
		else if(in[n] == '\n')
			out += "\\n";
		else
			out += in[n];
	}
	return out;
}

QString echoBlock(int tabs, const QString &in)
{
	QStringList pars = in.split('\n', QString::KeepEmptyParts);
	if(!pars.isEmpty() && pars.last().isEmpty())
		pars.removeLast();
	QStringList lines;
	int n;
	for(n = 0; n < pars.count(); ++n) {
		QStringList list = wrapString(pars[n], CONF_WRAP);
		for(int n2 = 0; n2 < list.count(); ++n2)
			lines.append(list[n2]);
	}

	QString str;
	for(n = 0; n < lines.count(); ++n) {
		QString out;
		out.fill(9, tabs); // 9 == tab character
		if(lines[n].isEmpty())
			out += QString("printf \"\\n\"\n");
		else
			out += QString("printf \"%1\\n\"\n").arg(c_escape(lines[n]));
		str += out;
	}
	return str;
}

const char *qt4_info_str =
	"Be sure you have a proper Qt 4.0 build environment set up.  This means not just Qt, "
	"but also a C++ compiler, a make tool, and any other packages necessary "
	"for compiling C++ programs.\n"
	"\n"
	"If you are certain everything is installed, then it could be that Qt 4 is not being "
	"recognized or that a different version of Qt is being detected by mistake (for example, "
	"this could happen if \\$QTDIR is pointing to a Qt 3 installation).  At least one of "
	"the following conditions must be satisfied:\n"
	"\n"
	" 1) --qtdir is set to the location of Qt\n"
	" 2) \\$QTDIR is set to the location of Qt\n"
	" 3) QtCore is in the pkg-config database\n"
	" 4) qmake is in the \\$PATH\n"
	"\n"
	"This script will use the first one it finds to be true, checked in the above order.  #3 and #4 are the "
	"recommended options.  #1 and #2 are mainly for overriding the system configuration.\n"
	"\n";

class ConfUsageOpt
{
public:
	ConfUsageOpt(const QString &_name="", const QString &_arg="", const QString &_desc="")
	{
		name = _name;
		arg = _arg;
		desc = _desc;
	}

	QString generateFirst() const
	{
		QString line = QString("  --%1").arg(name);
		if(!arg.isEmpty())
			line += QString("=[%1]").arg(arg);
		return line;
	}

	QString generate(int indent, int width) const
	{
		QString str;
		QStringList descLines = wrapString(desc, width);
		bool first = true;
		//printf("lines:%d,indent:%d\n", descLines.count(), indent);
		for(QStringList::ConstIterator it = descLines.begin(); it != descLines.end(); ++it) {
			QString line;
			if(first) {
				line = generateFirst();
				first = false;
			}
			while((int)line.length() < indent)
				line += ' ';
			line += *it;
			str += line + '\n';
		}
		return str;
	}

	QString name, arg, desc;
};

class ConfOpt
{
public:
	ConfOpt(const QString &_name="", const QString &_arg="", const QString &_var="", const QString &_desc="")
	{
		name = _name;
		arg = _arg;
		var = _var;
		desc = _desc;
	}

	QString name, arg, var, desc;
};

class ConfGen
{
public:
	QList<ConfOpt> mainopts;
	QList<ConfOpt> appopts;
	QList<ConfOpt> depopts;
	QList<ConfOpt> all;
	QString name;
	QString profile;
	QByteArray filemodulescpp, filemodulesnewcpp, fileconfh, fileconfcpp, fileconfpro;
	bool libmode, usePrefix, useBindir, useIncdir, useLibdir, useDatadir;
	bool qt4, byoq;

	ConfGen()
	{
		libmode = false;
		usePrefix = true;
		useBindir = true;
		useIncdir = false;
		useLibdir = false;
		useDatadir = false;
		qt4 = false;
		byoq = false;

		// extra
		//extraopts += ConfOpt("zlib-inc", "path", "QC_ZLIB_INC", "Specify path to zlib include files.");
		//extraopts += ConfOpt("zlib-lib", "path", "QC_ZLIB_LIB", "Specify path to zlib library files.");
		//extraopts += ConfOpt("disable-dnotify", "", "QC_DISABLE_DNOTIFY", "Disable Linux DNOTIFY.");
	}

	void addDepOption(const QString &name, const QString &arg, const QString &var, const QString &desc)
	{
		ConfOpt opt;
		opt.name = name;
		opt.arg = arg;
		opt.var = var;
		opt.desc = desc;
		depopts += opt;
	}

	void addAppOption(const QString &name, const QString &arg, const QString &var, const QString &desc)
	{
		ConfOpt opt;
		opt.name = name;
		opt.arg = arg;
		opt.var = var;
		opt.desc = desc;
		appopts += opt;
	}

	void addOption(const QString &section, const QString &name, const QString &arg, const QString &var, const QString &desc)
	{
		if(section == "project")
			addAppOption(name, arg, var, desc);
		else
			addDepOption(name, arg, var, desc);
	}

	QByteArray generate()
	{
		// main options
		mainopts.clear();
		if(usePrefix) {
			mainopts += ConfOpt("prefix", "path", "PREFIX", "Base path for build/install.  Default: /usr/local");
			if(useBindir)
				mainopts += ConfOpt("bindir", "path", "BINDIR", "Directory for binaries.  Default: PREFIX/bin");
			if(useIncdir)
				mainopts += ConfOpt("includedir", "path", "INCDIR", "Directory for headers.  Default: PREFIX/include");
			if(useLibdir)
				mainopts += ConfOpt("libdir", "path", "LIBDIR", "Directory for libraries.  Default: PREFIX/lib");
			if(useDatadir)
				mainopts += ConfOpt("datadir", "path", "DATADIR", "Directory for data.  Default: PREFIX/share");
		}
		if(!byoq)
			mainopts += ConfOpt("qtdir", "path", "EX_QTDIR", "Directory where Qt is installed.");

		if(libmode)
			mainopts += ConfOpt("static", QString(), "QC_STATIC", "Create a static library instead of shared.");

		QString str;
		str += genHeader();
		str += genUsage();
		str += genFindStuff();
		str += genQtInfo();

		// combine main and extra opts together
		all = mainopts + appopts + depopts;

		/*str +=
		"# save environment variable\n"
		"ORIG_QTDIR=$QTDIR\n\n";*/

		// argument parsing
		str += createConfArgsSection();

		// set the builtin defaults
		if(usePrefix) {
			str += "PREFIX=${PREFIX:-/usr/local}\n";
			if(useBindir)
				str += "BINDIR=${BINDIR:-$PREFIX/bin}\n";
			if(useIncdir)
				str += "INCDIR=${INCDIR:-$PREFIX/include}\n";
			if(useLibdir)
				str += "LIBDIR=${LIBDIR:-$PREFIX/lib}\n";
			if(useDatadir)
				str += "DATADIR=${DATADIR:-$PREFIX/share}\n";
		}
		str += '\n';

		str += QString("echo \"Configuring %1 ...\"\n\n").arg(name);

		// display values
		str += "if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n";
		str += "echo\n";
		for(QList<ConfOpt>::ConstIterator it = all.begin(); it != all.end(); ++it) {
			const ConfOpt &i = *it;
			str += QString("echo %1=$%2\n").arg(i.var).arg(i.var);
		}
		str += "echo\n";
		str += "fi\n\n";

		if(qt4) {
			if(byoq) {
				str += "printf \"Preparing internal Qt 4 build environment ... \"\n\n";

				str += "cd byoq\n";
				str += "./byoq build\n";
				str += "ret=\"$?\"\n";
				str += "cd ..\n";
				str += "if [ \"$ret\" != \"0\" ]; then\n";
				str += "	exit 1\n";
				str += "fi\n";
				str += "unset QTDIR\n";
				str += "unset QMAKESPEC\n";
				// NOTE: if this is ever uncommented, remember
				//   that exporting with a set is a bashism
				//str += "if [ \"$QMAKESPEC\" == \"\" ]; then\n";
				//str += "	export QMAKESPEC=linux-g++\n";
				//str += "fi\n";
				str += "qm=$PWD/byoq/qt/bin/qmake\n\n";
			}

			str += "printf \"Verifying Qt 4 build environment ... \"\n\n";
			if(!byoq)
				str += genQt4Checks();
		}
		else {
			str += "printf \"Verifying Qt 3.x Multithreaded (MT) build environment ... \"\n\n";
			str += genQt3Checks();
		}

		str += genEmbeddedFiles();

		// export all values
		for(QList<ConfOpt>::ConstIterator it = all.begin(); it != all.end(); ++it) {
			const ConfOpt &i = *it;
			str += QString("export %1\n").arg(i.var);
		}
		str += "export QC_VERBOSE\n"; // export verbose flag also

		str += genDoQConf();

		// newer versions have this stuff in the conf program
		if(!qt4) {
			str += genRunExtra();
			str += genRunQMake();
		}

		str += genFooter();

		return str.toLatin1();
	}

private:
	QString genHeader()
	{
		QString str = QString(
		"#!/bin/sh\n"
		"#\n"
		"# Generated by qconf %1 ( http://delta.affinix.com/qconf/ )\n"
		"#\n"
		"\n"
		).arg(VERSION);
		return str;
	}

	QString genFooter()
	{
		QString str =
		"echo\n";
		//"if [ \"$QTDIR\" != \"$ORIG_QTDIR\" ]; then\n"
		//"	echo Good, your configure finished.  Now run \\'QTDIR=$QTDIR make\\'.\n"
		//"else\n"
		if(qt4)
			str += "echo \"Good, your configure finished.  Now run $MAKE.\"\n";
		else
			str += "echo \"Good, your configure finished.  Now run 'make'.\"\n";
		//"fi\n"
		str += "echo\n";
		return str;
	}

	int getUsageIndent(const QList<ConfUsageOpt> list)
	{
		int largest = 0;
		for(QList<ConfUsageOpt>::ConstIterator it = list.begin(); it != list.end(); ++it) {
			const ConfUsageOpt &opt = *it;
			QString tmp = opt.generateFirst();
			if((int)tmp.length() > largest)
				largest = tmp.length();
		}
		return largest;
	}

	QList<ConfUsageOpt> optsToUsage(const QList<ConfOpt> &list)
	{
		QList<ConfUsageOpt> out;
		for(QList<ConfOpt>::ConstIterator it = list.begin(); it != list.end(); ++it) {
			const ConfOpt &i = *it;
			out += ConfUsageOpt(i.name, i.arg, i.desc);
		}
		return out;
	}

	QString genUsageSection(const QString &title, const QList<ConfUsageOpt> &list)
	{
		QString str;
		str += title;
		str += '\n';
		int indent = getUsageIndent(list) + CONF_USAGE_SPACE;
		for(QList<ConfUsageOpt>::ConstIterator it = list.begin(); it != list.end(); ++it) {
			const ConfUsageOpt &opt = *it;
			str += opt.generate(indent, CONF_WRAP - indent);
		}
		str += "\n";
		return str;
	}

	QString genUsage()
	{
		QString str =
		"show_usage() {\ncat <<EOT\n"
		"Usage: $0 [OPTION]...\n\n"
		"This script creates necessary configuration files to build/install.\n\n";

		QList<ConfUsageOpt> list = optsToUsage(mainopts);
		list += ConfUsageOpt("verbose",  "",   "Show extra configure output.");
		list += ConfUsageOpt("help",   "",     "This help text.");
		str += genUsageSection("Main options:", list);

		if(!appopts.isEmpty()) {
			list = optsToUsage(appopts);
			str += genUsageSection("Project options:", list);
		}

		if(!depopts.isEmpty()) {
			list = optsToUsage(depopts);
			str += genUsageSection("Dependency options:", list);
		}

		str += "EOT\n}\n\n";
		return str;
	}

	QString genFindStuff()
	{
		QString str;

		// which
		str +=
		"# which/make detection adapted from Qt\n"
		"which_command() {\n"
		"	OLD_HOME=$HOME\n"
		"	HOME=/dev/null\n"
		"	export HOME\n"
		"\n"
		"	WHICH=`which which 2>/dev/null`\n"
		"	if echo $WHICH | grep 'shell built-in command' >/dev/null 2>&1; then\n"
		"		WHICH=which\n"
		"	elif [ -z \"$WHICH\" ]; then\n"
		"		if which which >/dev/null 2>&1; then\n"
		"			WHICH=which\n"
		"		else\n"
		"			for a in /usr/ucb /usr/bin /bin /usr/local/bin; do\n"
		"				if [ -x $a/which ]; then\n"
		"					WHICH=$a/which\n"
		"					break;\n"
		"				fi\n"
		"			done\n"
		"		fi\n"
		"	fi\n"
		"\n"
		"	if [ -z \"$WHICH\" ]; then\n"
		"		OLD_IFS=$IFS\n"
		"		IFS=:\n"
		"		for a in $PATH; do\n"
		"			if [ -x $a/$1 ]; then\n"
		"				echo \"$a/$1\"\n"
		"				IFS=$OLD_IFS\n"
		"				export IFS\n"
		"				HOME=$OLD_HOME\n"
		"				export HOME\n"
		"				return 0\n"
		"			fi\n"
		"		done\n"
		"		IFS=$OLD_IFS\n"
		"		export IFS\n"
		"	else\n"
		"		a=`\"$WHICH\" \"$1\" 2>/dev/null`\n"
		"		if [ ! -z \"$a\" -a -x \"$a\" ]; then\n"
		"			echo \"$a\"\n"
		"			HOME=$OLD_HOME\n"
		"			export HOME\n"
		"			return 0\n"
		"		fi\n"
		"	fi\n"
		"	HOME=$OLD_HOME\n"
		"	export HOME\n"
		"	return 1\n"
		"}\n"
		"WHICH=which_command\n"
		"\n";

		// make
		str +=
		"# find a make command\n"
		"if [ -z \"$MAKE\" ]; then\n"
		"	MAKE=\n"
		"	for mk in gmake make; do\n"
		"		if $WHICH $mk >/dev/null 2>&1; then\n"
		"			MAKE=`$WHICH $mk`\n"
		"			break\n"
		"		fi\n"
		"	done\n"
		"	if [ -z \"$MAKE\" ]; then\n"
		"		echo \"You don't seem to have 'make' or 'gmake' in your PATH.\"\n"
		"		echo \"Cannot proceed.\"\n"
		"		exit 1\n"
		"	fi\n"
		"fi\n"
		"\n";

		return str;
	}

	QString genQtInfo()
	{
		QString str =
		"show_qt_info() {\n";
		str += echoBlock(1, qt4_info_str);
		str +=
		"}\n\n";
		return str;
	}

	QString genConfArg(const QString &name, const QString &var, bool arg=true)
	{
		QString str;
		if(arg) {
			str = QString(
			"		--%1=*)\n"
			//"			%2=`expr \"${1}\" : \"--%3=\\(.*\\)\"`\n"
			//"			%2=\"${1#--%3=}\"\n"
			"			%2=$optarg\n"
			"			shift\n"
			"			;;\n"
			"\n").arg(name).arg(var); //.arg(name);
		}
		else {
			str = QString(
			"		--%1)\n"
			"			%2=\"Y\"\n"
			"			shift\n"
			"			;;\n"
			"\n").arg(name).arg(var);
		}
		return str;
	}

	QString createConfArgsSection()
	{
		char argsheader[] =
		"while [ $# -gt 0 ]; do\n"
		"	optarg=`expr \"x$1\" : 'x[^=]*=\\(.*\\)'`\n"
		"	case \"$1\" in\n";

		char argsfooter[] =
		"		--verbose)\n"
		"			QC_VERBOSE=\"Y\"\n"
		"			shift\n"
		"			;;\n"
		"		--help) show_usage; exit ;;\n"
		"		*) show_usage; exit ;;\n"
		"	esac\n"
		"done\n\n";

		QString str;
		str += argsheader;
		for(QList<ConfOpt>::ConstIterator it = mainopts.begin(); it != mainopts.end(); ++it)
			str += genConfArg((*it).name, (*it).var, !(*it).arg.isEmpty());
		for(QList<ConfOpt>::ConstIterator it = appopts.begin(); it != appopts.end(); ++it)
			str += genConfArg((*it).name, (*it).var, !(*it).arg.isEmpty());
		for(QList<ConfOpt>::ConstIterator it = depopts.begin(); it != depopts.end(); ++it)
			str += genConfArg((*it).name, (*it).var, !(*it).arg.isEmpty());
		str += argsfooter;
		return str;
	}

	QString genQt3Checks()
	{
		QStringList qtloc;
		qtloc += "/usr/lib/qt";
		qtloc += "/usr/share/qt";
		qtloc += "/usr/share/qt3";
		qtloc += "/usr/local/lib/qt";
		qtloc += "/usr/local/share/qt";
		qtloc += "/usr/lib/qt3";
		qtloc += "/usr/local/lib/qt3";
		qtloc += "/usr/X11R6/share/qt";
		qtloc += "/usr/qt/3";

		QString for_items;
		for(QStringList::ConstIterator it = qtloc.begin(); it != qtloc.end(); ++it) {
			for_items += (*it) + ' ';
		}

		QString str =
		"if [ -z \"$QTDIR\" ]; then\n"
		"	if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"		echo \\$QTDIR not set... trying to find Qt manually\n"
		"	fi\n";
		str += QString(
		"	for p in %1; do\n"
		).arg(for_items);
		str +=
		"		if [ -d \"$p/mkspecs\" ]; then\n"
		"			QTDIR=$p\n"
		"			break;\n"
		"		fi;\n"
		"	done\n"
		"	if [ -z \"$QTDIR\" ]; then\n"
		"		echo fail\n"
		"		echo\n"
		"		echo \"Unable to find Qt 'mkspecs'.  Perhaps you need to\"\n"
		"		echo \"install the Qt 3 development utilities.  You may download\"\n"
		"		echo \"them either from the vendor of your operating system\"\n"
		"		echo \"or from http://www.trolltech.com/\"\n"
		"		echo\n"
		"		echo \"If you're sure you have the Qt development utilities\"\n"
		"		echo \"installed, you might try using the --qtdir option.\"\n"
		"		echo\n"
		"		exit 1;\n"
		"	fi\n"
		"	if [ ! -x \"$QTDIR/bin/moc\" ]; then\n"
		"		m=`which moc 2>/dev/null`\n"
		"		if [ ! -x \"$m\" ]; then\n"
		"			echo fail\n"
		"			echo\n"
		"			echo \"We found Qt in $QTDIR, but we were unable to locate\"\n"
		"			echo \"the moc utility.  It was not found in $QTDIR/bin\"\n"
		"			echo \"nor in PATH.  This seems to be a very unusual setup.\"\n"
		"			echo \"You might try using the --qtdir option.\"\n"
		"			echo\n"
		"			exit 1;\n"
		"		fi\n"
		"		qtpre=`echo $m | awk '{ n = index($0, \"/bin/moc\"); if (!n) { exit 1; } print substr($0, 0, n-1); exit 0; }' 2>/dev/null`\n"
		"		ret=\"$?\"\n"
		"		if [ \"$ret\" != \"0\" ]; then\n"
		"			echo fail\n"
		"			echo\n"
		"			echo \"We found Qt in $QTDIR, but the location of moc\"\n"
		"			echo \"($m) is not suitable for use with this build system.\"\n"
		"			echo \"This is a VERY unusual and likely-broken setup.  You\"\n"
		"			echo \"should contact the maintainer of your Qt package.\"\n"
		"			echo\n"
		"			exit 1;\n"
		"		fi\n"
		"		QTDIR=$qtpre\n"
		"	fi\n"
		"fi\n"
		"\n"
		"if [ ! -x \"$QTDIR/bin/qmake\" ]; then\n"
		"	if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"		echo Warning: qmake not in \\$QTDIR/bin/qmake\n"
		"		echo trying to find it in \\$PATH\n"
		"	fi\n"
		"	qm=`which qmake 2>/dev/null`\n"
		"	if [ -x \"$qm\" ]; then\n"
		"		if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"			echo qmake found in $qm\n"
		"		fi\n"
		"	else\n"
		"		echo fail\n"
		"		echo\n"
		"		echo Sorry, you seem to have a very unusual setup,\n"
		"		echo or I missdetected \\$QTDIR=$QTDIR\n"
		"		echo\n"
		"		echo Please set \\$QTDIR manually and make sure that\n"
		"		echo \\$QTDIR/bin/qmake exists.\n"
		"		echo\n"
		"		exit 1;\n"
		"	fi\n"
		"else\n"
		"	qm=$QTDIR/bin/qmake\n"
		"fi\n\n";
		return str;
	}

	QString genQt4Checks()
	{
		QString str =
		"# run qmake -v and check version\n"
		"qmake_check_v4() {\n"
		"	if [ -x \"$1\" ]; then\n"
		"		if echo `$1 -v 2>&1` | grep \"Qt version 4\\.\" >/dev/null 2>&1; then\n"
		"			return 0\n"
		"		elif [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"			echo \"Warning: $1 not for Qt 4\"\n"
		"		fi\n"
		"	fi\n"
		"	return 1\n"
		"}\n"
		"\n";

		str +=
		"if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"	echo\n"
		"fi\n"
		"\n"
		"qm=\"\"\n"
		"names=\"qmake-qt4 qmake4 qmake\"\n"
		"\n"
		"# qt4 check: --qtdir\n"
		"if [ -z \"$qm\" ] && [ ! -z \"$EX_QTDIR\" ]; then\n"
		"	for n in $names; do\n"
		"		qstr=$EX_QTDIR/bin/$n\n"
		"		if qmake_check_v4 \"$qstr\"; then\n"
		"			qm=$qstr\n"
		"			break;\n"
		"		fi\n"
		"	done\n"
		"fi\n"
		"if [ -z \"$qm\" ] && [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"	echo \"Warning: qmake not found via --qtdir\"\n"
		"fi\n"
		"\n"
		"# qt4 check: QTDIR\n"
		"if [ -z \"$qm\" ] && [ ! -z \"$QTDIR\" ]; then\n"
		"	for n in $names; do\n"
		"		qstr=$QTDIR/bin/$n\n"
		"		if qmake_check_v4 \"$qstr\"; then\n"
		"			qm=$qstr\n"
		"			break;\n"
		"		fi\n"
		"	done\n"
		"fi\n"
		"if [ -z \"$qm\" ] && [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"	echo \"Warning: qmake not found via \\$QTDIR\"\n"
		"fi\n"
		"\n"
		"# qt4 check: pkg-config\n"
		"if [ -z \"$qm\" ]; then\n"
		"	str=`pkg-config QtCore --variable=exec_prefix 2>/dev/null`\n"
		"	if [ ! -z \"$str\" ]; then\n"
		"		for n in $names; do\n"
		"			qstr=$str/bin/$n\n"
		"			if qmake_check_v4 \"$qstr\"; then\n"
		"				qm=$qstr\n"
		"				break;\n"
		"			fi\n"
		"		done\n"
		"	fi\n"
		"fi\n"
		"if [ -z \"$qm\" ] && [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"	echo \"Warning: qmake not found via pkg-config\"\n"
		"fi\n"
		"\n"
		"# qt4 check: PATH\n"
		"if [ -z \"$qm\" ]; then\n"
		"	for n in $names; do\n"
		"		qstr=`$WHICH $n 2>/dev/null`\n"
		"		if qmake_check_v4 \"$qstr\"; then\n"
		"			qm=$qstr\n"
		"			break;\n"
		"		fi\n"
		"	done\n"
		"fi\n"
		"if [ -z \"$qm\" ] && [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"	echo \"Warning: qmake not found via \\$PATH\"\n"
		"fi\n"
		"\n"
		"if [ -z \"$qm\" ]; then\n"
		"	if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"		echo \" -> fail\"\n"
		"	else\n"
		"		echo \"fail\"\n"
		"	fi\n";

		str += echoBlock(1,
		"\n"
		"Reason: Unable to find the 'qmake' tool for Qt 4.\n"
		"\n");
		str +=
		"	show_qt_info\n";
		str +=
		"	exit 1;\n"
		"fi\n"
		"if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
		"	echo qmake found in $qm\n"
		"fi\n\n";
		return str;
	}

	QString genDoQConf()
	{
		QString outdir = ".qconftemp";
		QString cleanup = QString("rm -rf %1").arg(outdir);

		QString str;
		str += QString("%1\n").arg(cleanup);

		str += QString(
		"(\n"
		"	mkdir %1\n"
		"	gen_files %2\n"
		"	cd %3\n"
		).arg(outdir).arg(outdir).arg(outdir);

		if(qt4) {
			str +=
			"	$qm conf4.pro >/dev/null\n"
			"	$MAKE clean >/dev/null 2>&1\n"
			"	$MAKE >../conf.log 2>&1\n";
		}
		else {
			str +=
			"	$qm conf.pro >/dev/null\n"
			"	QTDIR=$QTDIR make clean >/dev/null 2>&1\n"
			"	QTDIR=$QTDIR make >../conf.log 2>&1\n";
		}
		str += ")\n\n";

		if(qt4) {
			str += QString(
			"if [ \"$?\" != \"0\" ]; then\n"
			"	%1\n"
			"	if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
			"		echo \" -> fail\"\n"
			"	else\n"
			"		echo \"fail\"\n"
			"	fi\n").arg(cleanup);

			str += echoBlock(1,
			"\n"
			"Reason: There was an error compiling 'conf'.  See conf.log for details.\n"
			"\n");
			if(!byoq)
			{
				str +=
				"	show_qt_info\n";
			}

			str +=
			"	if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
			"		echo \"conf.log:\"\n"
			"		cat conf.log\n"
			"	fi\n";

			str +=
			"	exit 1;\n"
			"fi\n\n";
		}
		else {
			str += QString(
			"if [ \"$?\" != \"0\" ]; then\n"
			"	%1\n"
			"	echo fail\n"
			"	echo\n"
			"	echo \"There was an error compiling 'conf'.  Be sure you have a proper\"\n"
			"	echo \"Qt 3.x Multithreaded (MT) build environment set up.  This\"\n"
			"	echo \"means not just Qt, but also a C++ compiler, the 'make' command,\"\n"
			"	echo \"and any other packages necessary to compile C++ programs.\"\n"
			"	echo \"See conf.log for details.\"\n"
			"	if [ ! -f \"$QTDIR/lib/libqt-mt.so.3\" ]; then\n"
			"		echo\n"
			"		echo \"One possible reason is that you don't have\"\n"
			"		echo \"libqt-mt.so.3 installed in $QTDIR/lib/.\"\n"
			"	fi\n"
			"	echo\n"
			"	exit 1;\n"
			"fi\n\n").arg(cleanup);
		}

		if(qt4) {
			str += QString("QC_COMMAND=$0\n");
			str += QString("export QC_COMMAND\n");
			str += QString("QC_PROFILE=%1\n").arg(profile);
			str += QString("export QC_PROFILE\n");
			str += QString("QC_QMAKE=$qm\n");
			str += QString("export QC_QMAKE\n");
			str += QString("QC_MAKETOOL=$MAKE\n");
			str += QString("export QC_MAKETOOL\n");
		}

		str += QString("%1/conf\n").arg(outdir);

		str += "ret=\"$?\"\n";
		str += "if [ \"$ret\" = \"1\" ]; then\n";
		str += QString("	%1\n").arg(cleanup);
		str += "	echo\n";
		str += "	exit 1;\n";
		str += "else\n";
		str += "	if [ \"$ret\" != \"0\" ]; then\n";
		str += QString("		%1\n").arg(cleanup);

		if(qt4) {
			str +=
			"		if [ \"$QC_VERBOSE\" = \"Y\" ]; then\n"
			"			echo \" -> fail\"\n"
			"		else\n"
			"			echo \"fail\"\n"
			"		fi\n";
		}
		else
			str += "		echo fail\n";

		str += "		echo\n";
		if(qt4)
			str += "		echo \"Reason: Unexpected error launching 'conf'\"\n";
		else
			str += "		echo \"Unexpected error launching 'conf'\"\n";
		str += "		echo\n";
		str += "		exit 1;\n";
		str += "	fi\n";
		str += "fi\n";
		str += QString("%1\n\n").arg(cleanup);

		return str;
	}

	QString genRunExtra()
	{
		QString str =
		"if [ -x \"./qcextra\" ]; then\n"
		"	./qcextra\n"
		"fi\n";
		return str;
	}

	QString genRunQMake()
	{
		QString str;
		str += "# run qmake\n";
		str += QString("$qm %1\n").arg(profile);
		str +=
		"if [ \"$?\" != \"0\" ]; then\n"
		"	echo\n"
		"	exit 1;\n"
		"fi\n";

		if(!qt4) {
			str +=
			"cat >Makefile.tmp <<EOT\n"
			"export QTDIR = $QTDIR\n"
			"export PATH = $QTDIR/bin:$PATH\n"
			"EOT\n"
			"cat Makefile >> Makefile.tmp\n"
			"rm -f Makefile\n"
			"cp -f Makefile.tmp Makefile\n"
			"rm -f Makefile.tmp\n";
		}

		str += "\n";

		return str;
	}

	QString genEmbeddedFile(const QString &name, const QByteArray &a)
	{
		QString str;
		str += QString("cat >%1 <<EOT\n").arg(name);
		str += escapeFile(QString::fromLatin1(a));
		str += "\nEOT\n";
		return str;
	}

	QString genEmbeddedFiles()
	{
		QString str;
		str += "gen_files() {\n";
		str += genEmbeddedFile("$1/modules.cpp", filemodulescpp);
		str += genEmbeddedFile("$1/modules_new.cpp", filemodulesnewcpp);
		str += genEmbeddedFile(qt4 ? "$1/conf4.h" : "$1/conf.h", fileconfh);
		str += genEmbeddedFile(qt4 ? "$1/conf4.cpp" : "$1/conf.cpp", fileconfcpp);
		str += genEmbeddedFile(qt4 ? "$1/conf4.pro" : "$1/conf.pro", fileconfpro);
		str += "}\n\n";
		return str;
	}
};

static QStringList getQCMODLines(const QByteArray &in)
{
	QString str = QString::fromLatin1(in);
	QString begin = "-----BEGIN QCMOD-----\n";
	QString end = "-----END QCMOD-----\n";
	int n = str.indexOf(begin);
	if(n == -1)
		return QStringList();
	int x = n + begin.length();
	n = str.indexOf(end, x);
	if(n == -1)
		return QStringList();
	QString datarea = str.mid(x, n-x);
	QStringList lines = datarea.split('\n', QString::SkipEmptyParts);
	return lines;
}

static bool parseArg(const QString &in, QString *_name, QString *_arg, QString *_desc)
{
	QString name;
	QString desc;
	int n = in.indexOf(',');
	if(n == -1) {
		name = in;
		desc = "";
	}
	else {
		name = in.mid(0, n);
		++n;
		desc = in.mid(n);
	}
	n = name.indexOf("=[");
	QString arg;
	if(n != -1) {
		n += 2;
		int n2 = name.indexOf(']', n);
		if(n2 == -1)
			return false;
		arg = name.mid(n, n2-n);
		n -= 2;
		name = name.mid(0, n);
	}
	*_name = name;
	*_arg  = arg;
	*_desc = desc;
	return true;
}

struct QCModArg
{
	QString name, arg, desc;
};

class QCModInfo
{
public:
	QString longname;
	QString section;
	QList<QCModArg> args;

	static QCModInfo getModInfo(const QByteArray &buf)
	{
		QCModInfo info;
		QStringList lines = getQCMODLines(buf);
		for(QStringList::ConstIterator it = lines.begin(); it != lines.end(); ++it) {
			const QString &line = *it;
			int n = line.indexOf(':');
			if(n == -1)
				continue;
			QString type = line.mid(0, n).toLower();
			// find next non-whitespace
			++n;
			for(; n < (int)line.length(); ++n) {
				if(!line[n].isSpace())
					break;
			}
			QString rest = line.mid(n);

			if(type == "name") {
				info.longname = rest;
			}
			else if(type == "section") {
				info.section = rest;
			}
			else if(type == "arg") {
				QString name, arg, desc;
				if(!parseArg(rest, &name, &arg, &desc))
					continue;
				QCModArg a;
				a.name = name;
				a.arg = arg;
				a.desc = desc;
				info.args += a;
			}
		}

		return info;
	}
};

const char * str2out(const QString &str)
{
	return qPrintable(str);
}

enum VersionMode { VersionMin, VersionExact, VersionMax, VersionAny };

class Dep
{
public:
	Dep()
	{
		required = false;
		disabled = false;
		pkgconfig = false;
	}

	QString name, longname, section;
	bool required;
	bool disabled;
	QList<QCModArg> args;

	bool pkgconfig;
	QString pkgname;
	VersionMode pkgvermode;
	QString pkgver;
};

class Conf
{
public:
	Conf()
	{
		libmode = false;
		noprefix = false;
		nobindir = false;
		useincdir = false;
		uselibdir = false;
		qt4 = false;
		byoq = false;
	}

	QString name, profile;
	QList<Dep> deps;
	QList<QCModArg> args;
	bool libmode, noprefix, nobindir, useincdir, uselibdir, usedatadir;
	QStringList moddirs;
	bool qt4, byoq;
};

Conf xmlToConf(const QDomElement &e)
{
	Conf conf;
	conf.name = e.elementsByTagName("name").item(0).toElement().text();

	conf.profile = e.elementsByTagName("profile").item(0).toElement().text();

	QDomNodeList nl = e.elementsByTagName("dep");
	for(int n = 0; n < (int)nl.count(); ++n) {
		QDomElement i = nl.item(n).toElement();
		Dep dep;
		dep.name = i.attribute("type");
		if(dep.name == "pkg") {
			dep.name = i.attribute("name");
			dep.longname = dep.name;
			dep.pkgconfig = true;
			dep.pkgname = i.attribute("pkgname");
			QString str = i.attribute("version");
			VersionMode mode = VersionAny;
			QString ver;
			if(str.startsWith(">=")) {
				mode = VersionMin;
				ver = str.mid(2);
			}
			else if(str.startsWith("<=")) {
				mode = VersionMax;
				ver = str.mid(2);
			}
			else if(!str.isEmpty()) {
				mode = VersionExact;
				ver = str;
			}
			dep.pkgvermode = mode;
			dep.pkgver = ver;
		}
		if(i.elementsByTagName("required").count() > 0)
			dep.required = true;
		if(i.elementsByTagName("disabled").count() > 0)
			dep.disabled = true;
		conf.deps += dep;
	}

	nl = e.elementsByTagName("arg");
	for(int n = 0; n < (int)nl.count(); ++n) {
		QDomElement i = nl.item(n).toElement();
		QCModArg a;
		a.name = i.attribute("name");
		a.arg = i.attribute("arg");
		a.desc = i.text();
		conf.args += a;
	}

	if(e.elementsByTagName("lib").count() > 0)
		conf.libmode = true;

	if(e.elementsByTagName("noprefix").count() > 0)
		conf.noprefix = true;

	if(e.elementsByTagName("nobindir").count() > 0)
		conf.nobindir = true;

	if(e.elementsByTagName("incdir").count() > 0)
		conf.useincdir = true;

	if(e.elementsByTagName("libdir").count() > 0)
		conf.uselibdir = true;

	if(e.elementsByTagName("datadir").count() > 0)
		conf.usedatadir = true;

	nl = e.elementsByTagName("moddir");
	for(int n = 0; n < (int)nl.count(); ++n) {
		QDomElement i = nl.item(n).toElement();
		conf.moddirs += i.text();
	}

	conf.qt4 = true;
	if(e.elementsByTagName("qt3").count() > 0)
		conf.qt4 = false;

	if(conf.qt4 && e.elementsByTagName("byoq").count() > 0)
		conf.byoq = true;

	return conf;
}

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);
	Conf conf;
	QString fname;
	bool skipLoad = false;

	if(argc < 2) {
		// try to find a .qc file
		QDir cur;
		QStringList list = cur.entryList(QStringList() << "*.qc");
		if(list.isEmpty()) {
			// try to find a .pro file to work from
			list = cur.entryList(QStringList() << "*.pro");
			if(list.isEmpty()) {
				printf("qconf: no .qc or .pro file found.\n");
				return 1;
			}
			QFileInfo fi(cur.filePath(list[0]));
			conf.name = fi.baseName();
			conf.profile = fi.fileName();

			// save to .qc
			fname = conf.name + ".qc";
			QFile f(fname);
			if(!f.open(QFile::WriteOnly | QFile::Truncate)) {
				printf("qconf: unable to write %s\n", str2out(fname));
				return 1;
			}
			QDomDocument doc;
			QDomElement e = doc.createElement("qconf");
			QDomElement i;
			i = doc.createElement("name");
			i.appendChild(doc.createTextNode(conf.name));
			e.appendChild(i);
			i = doc.createElement("profile");
			i.appendChild(doc.createTextNode(conf.profile));
			e.appendChild(i);
			doc.appendChild(e);
			QByteArray cs = doc.toString().toUtf8();
			f.write(cs);
			f.close();
			skipLoad = true;
		}
		else {
			fname = list[0];
		}
	}
	else {
		QString cs = argv[1];
		if(cs.left(2) == "--") {
			if(cs == "--help") {
				printf("Usage: qconf [.qc file]\n\n");
				printf("Options:\n");
				printf("  --version    Show version number\n");
				printf("  --help       This help\n");
				printf("\n");
				return 0;
			}
			else if(cs == "--version") {
				printf("qconf version: %s by Justin Karneges <justin@affinix.com>\n", VERSION);
				return 0;
			}
			else {
				printf("Unknown option: %s\n", qPrintable(cs));
				return 0;
			}
		}
		fname = QFile::decodeName(QByteArray(argv[1]));
	}

	if(!skipLoad) {
		QFile f(fname);
		if(!f.open(QFile::ReadOnly)) {
			printf("qconf: error reading %s\n", str2out(f.fileName()));
			return 1;
		}
		QDomDocument doc;
		if(!doc.setContent(&f)) {
			printf("qconf: error parsing %s\n", str2out(f.fileName()));
			return 1;
		}
		f.close();

		QDomElement base = doc.documentElement();
		if(base.tagName() != "qconf") {
			printf("qconf: bad format of %s\n", str2out(f.fileName()));
			return 1;
		}
		conf = xmlToConf(base);
	}

	// see if the appdir looks like an in-place qconf build
	QString appdir = QCoreApplication::applicationDirPath();
	QString localDataPath;
	if(looksLikeInPlace(appdir))
		localDataPath = appdir;

	QStringList moddirs;
	if(!conf.moddirs.isEmpty())
		moddirs += conf.moddirs;

	QString confdirpath;
	if(!localDataPath.isEmpty()) {
		moddirs += localDataPath + "/modules";
		confdirpath = localDataPath + "/conf";
	}
	else {
		moddirs += QString(DATADIR) + "/qconf/modules";
		confdirpath = QString(DATADIR) + "/qconf/conf";
	}

	QDir confdir(confdirpath);
	if(!confdir.exists()) {
		printf("qconf: %s does not exist.\n", str2out(confdir.path()));
		return 1;
	}

	QFile f;
	QByteArray confh;
	if(conf.qt4) {
		f.setFileName(confdir.filePath("conf4.h"));
		if(!f.open(QFile::ReadOnly)) {
			printf("qconf: cannot read %s\n", str2out(f.fileName()));
			return 1;
		}
		confh = f.readAll();
		f.close();
	}

	f.setFileName(confdir.filePath(conf.qt4 ? "conf4.cpp" : "conf.cpp"));
	if(!f.open(QFile::ReadOnly)) {
		printf("qconf: cannot read %s\n", str2out(f.fileName()));
		return 1;
	}
	QByteArray confcpp = f.readAll();
	f.close();

	f.setFileName(confdir.filePath(conf.qt4 ? "conf4.pro" : "conf.pro"));
	if(!f.open(QFile::ReadOnly)) {
		printf("qconf: cannot read %s\n", str2out(f.fileName()));
		return 1;
	}
	QByteArray confpro = f.readAll();
	f.close();
	confpro += "\nDEFINES += HAVE_MODULES\n";

	printf("Project name: %s\n", str2out(conf.name));
	printf("Profile: %s\n", str2out(conf.profile));
	printf("Deps: ");
	if(conf.deps.isEmpty())
		printf("none\n");
	else {
		bool first = true;
		for(QList<Dep>::ConstIterator it = conf.deps.begin(); it != conf.deps.end(); ++it) {
			const Dep &dep = *it;
			printf("%s%s%s", first ? "": " ", str2out(dep.name), dep.required ? "*": "");
			first = false;
		}
		printf("\n");
	}
	printf("\n");

	// look up dep module information
	QByteArray allmods;
	QString modscreate;
	for(QList<Dep>::Iterator it = conf.deps.begin(); it != conf.deps.end(); ++it) {
		Dep &dep = *it;

		if(dep.pkgconfig) {
			QString desc = dep.longname;
			QString modestr = "VersionAny";
			if(dep.pkgvermode != VersionAny) {
				if(dep.pkgvermode == VersionMin) {
					desc += " >= ";
					modestr = "VersionMin";
				}
				else if(dep.pkgvermode == VersionMax) {
					desc += " <= ";
					modestr = "VersionMax";
				}
				else {
					desc += " ";
					modestr = "VersionExact";
				}
				desc += dep.pkgver;
			}
			modscreate += QString("    o = new qc_internal_pkgconfig(conf, \"%1\", \"%2\", %3, \"%4\");\n    o->required = %5;\n    o->disabled = %6;\n"
				).arg(dep.pkgname).arg(desc).arg(modestr).arg(dep.pkgver).arg(dep.required ? "true": "false").arg(dep.disabled ? "true": "false");
			continue;
		}

		// look for module
		QString modfname = QString("%1.qcm").arg(dep.name);
		QFileInfo fi;
		bool found = false;
		for(QStringList::ConstIterator mit = moddirs.begin(); mit != moddirs.end(); ++mit) {
			QDir moddir(*mit);
			fi.setFile(moddir.filePath(modfname));
			//printf("checking for: [%s]\n", fi.filePath().latin1());
			if(fi.exists()) {
				found = true;
				break;
			}
		}
		if(!found) {
			printf("qconf: no such module '%s'!\n", qPrintable(dep.name));
			return 1;
		}
		QFile mod(fi.filePath());
		if(!mod.open(QFile::ReadOnly)) {
			printf("qconf: error opening '%s'!\n", qPrintable(mod.fileName()));
			return 1;
		}
		QByteArray buf = mod.readAll();
		mod.close();

		QCModInfo info = QCModInfo::getModInfo(buf);
		dep.longname = info.longname;
		dep.section = info.section;
		dep.args = info.args;

		// prepend #line
		int oldsize = buf.size();
		QString str = QString("#line 1 \"%1\"\n").arg(modfname);
		QByteArray cs = str.toLocal8Bit();
		int len = cs.length();
		buf.resize(oldsize + len);
		memmove(buf.data() + len, buf.data(), oldsize);
		memcpy(buf.data(), cs.data(), len);

		// append to the module buffer
		oldsize = allmods.size();
		allmods.resize(oldsize + buf.size());
		memcpy(allmods.data() + oldsize, buf.data(), buf.size());

		modscreate += QString("    o = new qc_%1(conf);\n    o->required = %2;\n    o->disabled = %3;\n"
			).arg(escapeArg(dep.name)).arg(dep.required ? "true": "false").arg(dep.disabled ? "true": "false");
	}
	QByteArray modsnew = modscreate.toLatin1();

	// write configure
	QFile out;
	out.setFileName("configure");
	if(!out.open(QFile::WriteOnly | QFile::Truncate)) {
		printf("qconf: error writing configure\n");
		return 1;
	}
	ConfGen cg;
	cg.name = conf.name;
	cg.profile = conf.profile;
	if(conf.libmode)
		cg.libmode = true;
	if(conf.noprefix)
		cg.usePrefix = false;
	if(conf.nobindir)
		cg.useBindir = false;
	if(conf.useincdir)
		cg.useIncdir = true;
	if(conf.uselibdir)
		cg.useLibdir = true;
	if(conf.usedatadir)
		cg.useDatadir = true;
	if(conf.qt4)
		cg.qt4 = true;
	if(conf.byoq)
		cg.byoq = true;
	cg.filemodulescpp = allmods;
	cg.filemodulesnewcpp = modsnew;
	cg.fileconfh = confh;
	cg.fileconfcpp = confcpp;
	cg.fileconfpro = confpro;

	for(QList<Dep>::Iterator it = conf.deps.begin(); it != conf.deps.end(); ++it) {
		Dep &dep = *it;
		QString longname;
		if(!dep.longname.isEmpty())
			longname = dep.longname;
		else
			longname = dep.name;
		if(!dep.required && !dep.disabled)
			cg.addOption(dep.section, QString("disable-") + dep.name, "", QString("QC_DISABLE_") + escapeArg(dep.name), QString("Disable use of ") + longname);
		else if(dep.disabled)
			cg.addOption(dep.section, QString("enable-") + dep.name, "", QString("QC_ENABLE_") + escapeArg(dep.name), QString("Enable use of ") + longname);

		// extra dep args?
		for(QList<QCModArg>::ConstIterator ait = dep.args.begin(); ait != dep.args.end(); ++ait) {
			const QCModArg &a = *ait;
			cg.addOption(dep.section, a.name, a.arg, QString("QC_") + escapeArg(a.name.toUpper()), a.desc);
		}
	}

	// extra .qc args?
	for(QList<QCModArg>::ConstIterator it = conf.args.begin(); it != conf.args.end(); ++it) {
		const QCModArg &a = *it;
		cg.addAppOption(a.name, a.arg, QString("QC_") + escapeArg(a.name.toUpper()), a.desc);
	}

	QByteArray cs = cg.generate();
	out.write(cs);
	out.close();
	chmod("configure", 0755);

	printf("'configure' written.\n");

	return 0;
}
