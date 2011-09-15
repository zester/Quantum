/**
 * @file /src/eggwm/config/Config.cpp
 *
 * @~spanish
 * Este archivo es parte del proyecto Egg Window Manager, usted puede
 * redistribuirlo y/o modificarlo bajo los téminos de la licencia GNU GPL v3.
 *
 * @~english
 * This file is part of the Egg Window Manager project, you can redistribute it
 * and/or modify it under the terms of the GNU GPL v3.
 *
 * @class  Config
 * @author José Expósito
 */
#include "Config.h"

// ************************************************************************** //
// **********             STATIC METHODS AND VARIABLES             ********** //
// ************************************************************************** //

Config* Config::instance = NULL;

//------------------------------------------------------------------------------

const char* Config::USR_CONFIG_DIR       = "/usr/share/eggwm";
const char* Config::HOME_CONFIG_DIR      = ".eggwm";
const char* Config::CONFIG_FILE_PATH     = "/.eggwm/eggwm.conf";
const char* Config::USED_THEME           = "theme/name";

//------------------------------------------------------------------------------

const char* Config::THEMES_PATH          = "/.eggwm/themes/";

//------------------------------------------------------------------------------

const char* Config::THEME_INFO           = "/theme.inf";
const char* Config::STYLE_QSS            = "/style.qss";

//------------------------------------------------------------------------------

const char* Config::SHOW_ICON             = "theme/show_icon";

const char* Config::TITLEBAR_WIDTH        = "theme/titlebar_width";
const char* Config::TOP_BORDER_WIDTH      = "theme/top_border_width";
const char* Config::BOTTOM_BORDER_WIDTH   = "theme/bottom_border_width";
const char* Config::LEFT_BORDER_WIDTH     = "theme/left_border_width";
const char* Config::RIGHT_BORDER_WIDTH    = "theme/right_border_width";
const char* Config::ICON_SIZE             = "theme/icon_size";

const char* Config::MINIMIZE_BUTTON_POS   = "theme/minimize_button_pos";
const char* Config::MAXIMIZE_BUTTON_POS   = "theme/maximize_button_pos";
const char* Config::EXIT_BUTTON_POS       = "theme/exit_button_pos";
const char* Config::ICON_POS              = "theme/icon_pos";
const char* Config::TITLE_POS             = "theme/title_pos";

const char* Config::MINIMIZE_BUTTON_ALING = "theme/minimize_button_aling";
const char* Config::MAXIMIZE_BUTTON_ALING = "theme/maximize_button_aling";
const char* Config::EXIT_BUTTON_ALING     = "theme/exit_button_aling";

//------------------------------------------------------------------------------

bool                      Config::showIcon;
int                       Config::titlebarWidth;
int                       Config::topBorderWidth;
int                       Config::bottomBorderWidth;
int                       Config::leftBorderWidth;
int                       Config::rightBorderWidth;
int                       Config::iconSize;
QPair<Config::Aling, int> Config::minimizeButtonPos;
QPair<Config::Aling, int> Config::maximizeButtonPos;
QPair<Config::Aling, int> Config::exitButtonPos;
QPair<Config::Aling, int> Config::iconPos;
QPair<Config::Aling, int> Config::titlePos;
Config::Aling             Config::minimizeButtonAling;
Config::Aling             Config::maximizeButtonAling;
Config::Aling             Config::exitButtonAling;
QString                   Config::style;

//------------------------------------------------------------------------------

Config* Config::getInstance() {
    if(Config::instance == NULL) {
        Config::instance = new Config();
    }
    return Config::instance;
}

void Config::loadConfig() {
    // Si no existe configuración en $HOME la copiamos de /usr/share/eggwm
    QDir usrConfigDir(USR_CONFIG_DIR);
    QDir homeConfigDir(QDir::homePath() + "/" + HOME_CONFIG_DIR);

    if(!homeConfigDir.exists()) {
        qDebug() << "Home configuration not found, copying it...";

        if(!usrConfigDir.exists()) {
            qFatal("/usr/share/eggwm not found, reinstall the application can "
                   "solve the problem");
        }

        homeConfigDir.cdUp();
        homeConfigDir.mkdir(HOME_CONFIG_DIR);
        homeConfigDir.cd(HOME_CONFIG_DIR);

        if(!this->copyDir(usrConfigDir, homeConfigDir)) {
            qFatal("Can't copy configuration to your home");
        }
    }

    // Leemos la configuración
    qDebug() << "Reading configuration from home";
    QSettings eggwmSettings(QDir::homePath() + CONFIG_FILE_PATH,
            QSettings::NativeFormat);

    //--------------------------------------------------------------------------

    // Abrimos el archivo de configuración del tema
    QString folderThemeName = eggwmSettings.value(USED_THEME, "").toString();
    QString themeConfigPath = QDir::homePath() + THEMES_PATH + folderThemeName
            + THEME_INFO;
    QSettings themeSettings(themeConfigPath, QSettings::NativeFormat);

    // Guardamos la información del tema
    showIcon            = themeSettings.value(SHOW_ICON, false).toBool();

    titlebarWidth       = themeSettings.value(TITLEBAR_WIDTH, 16).toInt();
    topBorderWidth      = themeSettings.value(TOP_BORDER_WIDTH, 4).toInt();
    bottomBorderWidth   = themeSettings.value(BOTTOM_BORDER_WIDTH, 4).toInt();
    leftBorderWidth     = themeSettings.value(LEFT_BORDER_WIDTH, 16).toInt();
    rightBorderWidth    = themeSettings.value(RIGHT_BORDER_WIDTH, 16).toInt();
    iconSize            = themeSettings.value(ICON_SIZE, 16).toInt();

    minimizeButtonPos   = getItemPos(themeSettings, MINIMIZE_BUTTON_POS);
    maximizeButtonPos   = getItemPos(themeSettings, MAXIMIZE_BUTTON_POS);
    exitButtonPos       = getItemPos(themeSettings, EXIT_BUTTON_POS);
    iconPos             = getItemPos(themeSettings, ICON_POS);
    titlePos            = getItemPos(themeSettings, TITLE_POS);

    minimizeButtonAling = getIconAling(themeSettings, MINIMIZE_BUTTON_ALING);
    maximizeButtonAling = getIconAling(themeSettings, MAXIMIZE_BUTTON_ALING);
    exitButtonAling     = getIconAling(themeSettings, EXIT_BUTTON_ALING);

    //--------------------------------------------------------------------------

    // Guardamos el estilo
    QString themeStylePath = QDir::homePath() + THEMES_PATH + folderThemeName
            + STYLE_QSS;
    QFile qss(themeStylePath);
    qss.open(QFile::ReadOnly);
    style = qss.readAll();
    style.replace("%theme_path%", QDir::homePath()+THEMES_PATH+folderThemeName);
    qss.close();
}


// ************************************************************************** //
// **********                    PRIVATE METHODS                   ********** //
// ************************************************************************** //

bool Config::copyDir(QDir src, QDir dest) const {
    if(!src.isReadable())
        return false;

    QFileInfoList entries = src.entryInfoList();
    QList<QFileInfo>::iterator it;
    for(it=entries.begin(); it!=entries.end(); it++) {
        QFileInfo &finfo = *it;

        if(finfo.fileName()=="." || finfo.fileName()=="..") {
            // Nada
        } else if(finfo.isDir()) {
            dest.mkdir(finfo.fileName());
            src.cd(finfo.fileName());
            dest.cd(finfo.fileName());
            this->copyDir(src, dest);
            src.cdUp();
            dest.cdUp();
        } else if(finfo.isFile()) {
            QFile file(finfo.filePath());
            file.copy(dest.absoluteFilePath(finfo.fileName()));
        }
    }
    return true;
}

QPair<Config::Aling, int> Config::getItemPos(const QSettings& themeSettings,
        const QString& key) {
    QPair<Aling, int> pair;
    QString prop = themeSettings.value(key, "").toString();

    QString sa = prop.split(":").at(0);
    Aling a;
    if(sa == "left") a = LEFT;
    else if(sa == "center") a = CENTER;
    else a = RIGHT;
    pair.first = a;

    QString index = prop.split(":").at(1);
    pair.second = index.toInt();

    return pair;
}

Config::Aling Config::getIconAling(const QSettings& themeSettings,
        const QString& key) {
    Aling ia;
    QString prop = themeSettings.value(key, "").toString();

    if(prop == "top") ia = TOP;
    else if(prop == "bottom") ia = BOTTOM;
    else ia = CENTER;

    return ia;
}


// ************************************************************************** //
// **********                      GET/SET/IS                      ********** //
// ************************************************************************** //

int Config::getTitlebarWidth() const {
    return this->titlebarWidth;
}

int Config::getTopBorderWidth() const {
    return this->topBorderWidth;
}

int Config::getBottomBorderWidth() const {
    return this->bottomBorderWidth;
}

int Config::getLeftBorderWidth() const {
    return this->leftBorderWidth;
}

int Config::getRightBorderWidth() const {
    return this->rightBorderWidth;
}

int Config::getIconSize() const {
    return this->iconSize;
}

bool Config::isIconVisible() const {
    return this->showIcon;
}

QPair<Config::Aling, int> Config::getMinimizeButtonPos() const {
    return this->minimizeButtonPos;
}

QPair<Config::Aling, int> Config::getMaximizeButtonPos() const {
    return this->maximizeButtonPos;
}

QPair<Config::Aling, int> Config::getExitButtonPos() const {
    return this->exitButtonPos;
}

QPair<Config::Aling, int> Config::getIconPos() const {
    return this->iconPos;
}

QPair<Config::Aling, int> Config::getTitlePos() const {
    return this->titlePos;
}

Config::Aling Config::getMinimizeButtonAling() const {
    return this->minimizeButtonAling;
}

Config::Aling Config::getMaximizeButtonAling() const {
    return this->maximizeButtonAling;
}

Config::Aling Config::getExitButtonAling() const {
    return this->exitButtonAling;
}

QString Config::getStyle() const {
    return this->style;
}
