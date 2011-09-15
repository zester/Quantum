/*
 * stringhelp.cpp - string wrapping
 * Copyright (C) 2003-2005  Justin Karneges
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
 *
 */

#include "stringhelp.h"

static QString getNext(QString *str)
{
	if(str->isEmpty())
		return QString();

	// are we in space?
	int n = 0;
	if(str->at(n).isSpace())
	{
		// get out of it
		while(n < (int)str->length() && str->at(n).isSpace())
			++n;
		if(n == (int)str->length())
			return QString();
	}
	// find end or next space
	while(n < (int)str->length() && !str->at(n).isSpace())
		++n;
	QString result = str->mid(0, n);
	*str = str->mid(n);
	return result;
}

// wraps a string against a fixed width
QStringList wrapString(const QString &str, int wid)
{
	QStringList lines;
	QString cur;
	QString tmp = str;
	bool firstword = true;
	//printf("parsing: [%s]\n", qPrintable(tmp));
	while(1)
	{
		QString word = getNext(&tmp);
		if(word.isNull())
		{
			lines += cur;
			break;
		}
		//printf("word:[%s]\n", qPrintable(word));
		if(!cur.isEmpty())
		{
			if((int)cur.length() + (int)word.length() > wid)
			{
				lines += cur;
				cur = "";
			}
		}
		if(cur.isEmpty() && !firstword)
		{
			// trim the whitespace in front
			for(int n = 0; n < (int)word.length(); ++n)
			{
				if(!word.at(n).isSpace())
				{
					if(n > 0)
						word = word.mid(n);
					break;
				}
			}
		}
		cur += word;
		firstword = false;
	}
	return lines;
}
