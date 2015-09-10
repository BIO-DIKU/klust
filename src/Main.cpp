/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <iostream>
#include <string>

#include "Defines.h"
#include "MainControl.h"

#include "modules/NaiveClust.h"

static void printVersion() {
    std::cout << "This is the version.\n";
}

static void printHelp() {
    std::cout << "This is the help.\n";
}

static void analyseInput(int argc, char** argv) {
    if(argc <= 0 || argv == nullptr)
        return;

    std::string str(argv[0]);

    if(str.size() > 2 && str[0] == '-' && str[1] == '-') {
        if(str == "--id") {
            if(argc >= 2) {
                float id = std::stof(argv[1]);
                MainControl::instance()->setIdentity(id);
            }
            return analyseInput(argc-2, &(argv[2]));
        }
        else if(str == "--output") {

        }
        else if(str == "--format") {

        }
        else if(str == "--complement") {

        }
        else if(str == "--comparison") {

        }
        else if(str == "--sort_input") {

        }
        else if(str == "--keep_names") {

        }
        else if(str == "--score_encoding") {

        }
        else if(str == "--score_min") {

        }
        else if(str == "--max_rejects") {

        }
        else if(str == "--threads") {

        }
        else if(str == "--quiet") {

        }
        else if(str == "--version") {
            printVersion();
        }
        else if(str == "--verbose") {

        }
    }
    else if(str.size() > 1 && str[0] == '-') {

    }
    else {
        printHelp();
    }
}

int main(int argc, char** argv) {
    if(argc <= 1) {
        printHelp();
        return 0;
    }

    analyseInput(argc-1, &(argv[1]));

    //MainControl::instance()->setKmergen(new NaiveKmergen());
    //MainControl::instance()->setCompare(new NaiveCompare());
    //MainControl::instance()->setClust(new NaiveClust());

    return MainControl::instance()->run();
}
