#include "AppInfo.h"
#include "Ini.h"
#include "Log.h"
#include "MainWindow.h"
#include "VirtualReality.h"
#include "utils/Logger.h"
#include <QApplication>
#include <boost/program_options.hpp>
#include <boost/version.hpp>
#include <iostream>
#include <string>

using namespace std;
namespace bpo = boost::program_options;

int main(int argc, char *argv[])
{
   SET_FNAME("main()");
   bpo::options_description desc(string("Allowed options"));
   desc.add_options()("help,h", "Prints this message")("debug,d",
                                                       "Log debug info");
   bpo::positional_options_description pos;
   bpo::variables_map vm;
   store(bpo::command_line_parser(argc, argv)
            .options(desc)
            .positional(pos)
            .run(),
         vm);
   bpo::notify(vm);

   if (vm.count("help")) {
      clog << desc << endl;
      return 0;
   }
   bool logDebugModeIsOn(false);
   if (vm.count("debug")) {
      logDebugModeIsOn = true;
   }

   int r = 0;
   //----------------------------------------------------------------------
   //Core code
   auto &logger = utils::Logger::instance();
   LOGI("------------------------- " APPNAME " v" VERSION " started");
   LOGI("------------------------- BOOST libs: v" BOOST_LIB_VERSION);
   LOGI("------------------------- Qt: v" QT_VERSION_STR);
   logger.setDebugMode(logDebugModeIsOn);
   utils::INIreader &Ini = IniReader();
   try {
      Ini.setFileName("../data/YAAV.ini");
      Ini.init();
      LOGI("INIreader initialized");
      VirtualReality vr;
      vr.init();
      LOGI("Core code initialised");
      //-------------------------------------------------------------------
      //Qt code
      QApplication app(argc, argv);
      if (!QGLFormat::hasOpenGL()) {
         std::cerr << "This system has no OpenGL support" << std::endl;
         LOGE("This system has no OpenGL support");
         return 1;
      }
      MainWindow w(vr);
      w.show();
      r = app.exec();
   } catch (std::exception &x) {
      LOGE(x.what());
   } catch (...) {
      LOGE("UNKNOWN EXCEPTION");
   }
   LOGI("--------------------------- " APPNAME " v" VERSION " ended");

   return r;
}
