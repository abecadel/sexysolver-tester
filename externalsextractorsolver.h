/*  ExternalSextractorSolver for SexySolver Tester Application, developed by Robert Lancaster, 2020

    This application is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
*/

#ifndef EXTERNALSEXTRACTORSOLVER_H
#define EXTERNALSEXTRACTORSOLVER_H

#include "sexysolver.h"
#include <QProcess>
#include <QPointer>

class ExternalSextractorSolver : public SexySolver
{
    Q_OBJECT
public:
    explicit ExternalSextractorSolver(ProcessType type, Statistic imagestats, uint8_t *imageBuffer, QObject *parent);
    ~ExternalSextractorSolver();

    void abort() override;

    bool isRunning();

    QStringList getSolverArgsList();
    QStringList getClassicSolverArgsList();
    bool generateAstrometryConfigFile();

    QString fileToProcess;
    bool fileToProcessIsTempFile = false;
    int selectedStar;

    //External Options
    bool cleanupTemporaryFiles = true;
    bool autoGenerateAstroConfig = true;

    //System File Paths
    QStringList indexFilePaths;
    QString astapBinaryPath;
    QString sextractorBinaryPath;
    QString confPath;
    QString solverPath;
    QString wcsPath;

    //Methods to Set File Paths Automatically
    void setLinuxDefaultPaths();
    void setLinuxInternalPaths();
    void setMacHomebrewPaths();
    void setMacInternalPaths();
    void setWinANSVRPaths();
    void setWinCygwinPaths();

    // This is the xyls file path that sextractor will be saving for Astrometry.net
    // If it is not set, it will be set to a random temporary file
    QString sextractorFilePath;
    bool sextractorFilePathIsTempFile = false; //This will be set to true if it gets generated

    void logSolver();
    void logSextractor();

    int writeSextractorTable();
    int getSextractorTable();
    bool getSolutionInformation();
    bool getASTAPSolutionInformation();
    int saveAsFITS();
    void cleanupTempFiles();

    int loadWCS();
    wcs_point * getWCSCoord() override;
    QList<Star> getStarsWithRAandDEC() override;
    /// WCS Struct
    struct wcsprm *m_wcs
    {
        nullptr
    };
    int m_nwcs = 0;

private:
    QPointer<QProcess> solver;
    QPointer<QProcess> sextractorProcess;

    void run() override; //This starts the ExternalSextractorSolver in a separate thread.  Note, ExternalSextractorSolver uses QProcess

    int runExternalSextractor();
    int runExternalSolver();
    int runExternalClassicSolver();
    int runExternalASTAPSolver();

    //These are used for reading and writing the sextractor file
    char* xcol=strdup("X_IMAGE"); //This is the column for the x-coordinates
    char* ycol=strdup("Y_IMAGE"); //This is the column for the y-coordinates
    char* magcol=strdup("MAG_AUTO"); //This is the column for the magnitude
    char* colFormat=strdup("1E"); //This Format means a decimal number
    char* colUnits=strdup("pixels"); //This is the unit for the xy columns in the file
    char* magUnits=strdup("magnitude"); //This is the unit for the magnitude in the file

};

#endif // EXTERNALSEXTRACTORSOLVER_H
