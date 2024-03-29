/*
    HuwInterpreter is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HuwInterpreter is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HuwInterpreter.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FUNCTIONLIST_H
#define FUNCTIONLIST_H

// IO
#include "print.h"
#include "scan.h"
#include "command.h"

// Coversion
#include "not.h"
#include "str.h"

#include "asc.h"
#include "cha.h"
#include "instr.h"
#include "instrrev.h"
#include "tolower.h"
#include "left.h"
#include "len.h"
#include "ltrim.h"
#include "mid.h"
#include "replace.h"
#include "right.h"
#include "rtrim.h"
#include "space.h"
#include "strcomp.h"
#include "strreverse.h"
#include "trim.h"
#include "toupper.h"

// Date and Time
#include "weekday.h"
#include "weekdayname.h"
#include "year.h"
#include "now.h"
#include "month.h"
#include "monthname.h"
#include "currenttimefunction.h"

// File and directories
#include "fileread.h"
#include "filewrite.h"
#include "fileexists.h"
#include "dirfunction.h"

// Math
#include "abs.h"
#include "acos.h"
#include "asin.h"
#include "atan.h"
#include "atan2.h"
#include "ceil.h"
#include "cos.h"
#include "exp.h"
#include "floor.h"
#include "log.h"
#include "max.h"
#include "min.h"
#include "pow.h"
#include "sin.h"
#include "random.h"
#include "round.h"
#include "lround.h"
#include "sqrt.h"
#include "tan.h"

// Other
#include "print.h"
#include "println.h"
#include "emptyfunction.h"

//Array
#include "../functions/array.h"
#include "../functions/arrayunset.h"

// String/array
#include "../functions/count.h"

#include "isinttype.h"
#include "isdoubletype.h"
#include "isnumbertype.h"
#include "isstringtype.h"
#include "isarraytype.h"
#include "isnumbertype.h"

#include "isint.h"
#include "isdouble.h"
#include "isnumber.h"

#include "tonumber.h"
#include "todouble.h"
#include "tostring.h"

#include "regexsearch.h"
#include "regexreplace.h"
#include "regexmatch.h"

#include "clockfunction.h"
#include "timeformatfunction.h"

/*
#include "httpgetfunction.h"
#include "httppostfunction.h"
#include "httpputfunction.h"
#include "httpdeletefunction.h"
#include "httpheadfunction.h"
*/

#include "sleepfunction.h"

#include "jsonencodefunction.h"
#include "jsondecodefunction.h"

#include "sort.h"

#endif  //FUNCTIONLIST_H

