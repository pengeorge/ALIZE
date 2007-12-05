/*
Alize is a free, open tool for speaker recognition

Alize is a development project initiated by the ELISA consortium
  [www.lia.univ-avignon.fr/heberges/ALIZE/ELISA] and funded by the
  French Research Ministry in the framework of the
  TECHNOLANGUE program [www.technolangue.net]
  [www.technolangue.net]

The Alize project team wants to highlight the limits of voice 
  authentication in a forensic context.
  The following paper proposes a good overview of this point:
  [Bonastre J.F., Bimbot F., Boe L.J., Campbell J.P., Douglas D.A., 
  Magrin-chagnolleau I., Person  Authentification by Voice: A Need of 
  Caution, Eurospeech 2003, Genova]
  The conclusion of the paper of the paper is proposed bellow:
  [Currently, it is not possible to completely determine whether the 
  similarity between two recordings is due to the speaker or to other 
  factors, especially when: (a) the speaker does not cooperate, (b) there 
  is no control over recording equipment, (c) recording conditions are not 
  known, (d) one does not know whether the voice was disguised and, to a 
  lesser extent, (e) the linguistic content of the message is not 
  controlled. Caution and judgment must be exercised when applying speaker 
  recognition techniques, whether human or automatic, to account for these 
  uncontrolled factors. Under more constrained or calibrated situations, 
  or as an aid for investigative purposes, judicious application of these 
  techniques may be suitable, provided they are not considered as infallible.
  At the present time, there is no scientific process that enables one to 
  uniquely characterize a person=92s voice or to identify with absolute 
  certainty an individual from his or her voice.]
  Contact Jean-Francois Bonastre for more information about the licence or
  the use of Alize

Copyright (C) 2003-2005
  Laboratoire d'informatique d'Avignon [www.lia.univ-avignon.fr]
  Frederic Wils [frederic.wils@lia.univ-avignon.fr]
  Jean-Francois Bonastre [jean-francois.bonastre@lia.univ-avignon.fr]
          
This file is part of Alize.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#if !defined(ALIZE_TestMixtureServerFileWriter_cpp)
#define ALIZE_TestMixtureServerFileWriter_cpp

#ifdef WIN32
#pragma warning( disable : 4786 )
#endif

#include "TestMixtureServerFileWriter.h"
#include "MixtureServerFileWriter.h"
#include "MixtureServerFileReaderXml.h"
#include "MixtureServerFileReaderRaw.h"
#include "MixtureServer.h"
#include "Config.h"
#include <cstdio>

using namespace alize;

//-------------------------------------------------------------------------
TestMixtureServerFileWriter::TestMixtureServerFileWriter()
:Test() {}
//-------------------------------------------------------------------------
bool TestMixtureServerFileWriter::exec()
{
    Test::exec();

    {
        Config c;
        c.setParam("vectSize", "2");
        const String file("./TestMixtureServerFileWriter.xml");
        const String fileRaw("./TestMixtureServerFileWriter");

        // test method : String getClassName() const
        {
            test(MixtureServerFileWriter(file, c).getClassName()
                                    == "MixtureServerFileWriter", __LINE__);
        }

        // test method : explicit MixtureServerFileWriter(const FileName& f,
        //                                          const Config& c);
        {
            MixtureServerFileWriter w(file, c);
        }

        // test method : virtual void writeServer(const MixtureServer&);
        {
            MixtureServer ms(c), ms1(c);
            ms.setServerName("serverName");
            MixtureGD& mix0 = ms.createMixtureGD(3);
            DistribGD& d0 = mix0.getDistrib(0);
            DistribGD& d1 = mix0.getDistrib(1);
            DistribGD& d2 = mix0.getDistrib(2);
            mix0.weight(0) = 0.1;
            mix0.weight(1) = 0.2;
            mix0.weight(2) = 0.7;
            d0.setMean(1.1, 0);
            d0.setMean(2.2, 1);
            d0.setCov(3.3, 0);
            d0.setCov(4.4, 1);
            d0.setCov(3.3, 0);
            d0.setCov(4.4, 1);
            d1.setMean(5.5, 0);
            d1.setMean(6.6, 1);
            d1.setCov(7.7, 0);
            d1.setCov(8.8, 1);
            d2.setMean(9.9, 0);
            d2.setMean(10.1, 1);
            d2.setCov(11.11, 0);
            d2.setCov(12.12, 1);
            mix0.computeAll();

            MixtureGD& mix1 = ms.createMixtureGD(0);
            mix1.addDistrib(K::k, d2);
            mix1.addDistrib(K::k, d2);
            mix1.addDistrib(K::k, d0);
            mix1.weight(0) = 0.4;
            mix1.weight(1) = 0.5;
            mix1.weight(2) = 0.1;

            MixtureServerFileWriter w(file, c);
            w.writeMixtureServer(ms);
            w.close();
            
            MixtureServerFileReaderXml r(file, c);
            r.readMixtureServer(ms1);
            test (ms1.getServerName() == ms.getServerName(), __LINE__);
            test (ms1.getDistribCount() == ms.getDistribCount(), __LINE__);
            test (ms1.getMixtureCount() == ms.getMixtureCount(), __LINE__);
            test (ms1.getDistrib(0) == ms.getDistrib(0), __LINE__);
            test (ms1.getDistrib(1) == ms.getDistrib(1), __LINE__);
            test (ms1.getDistrib(2) == ms.getDistrib(2), __LINE__);
            test (ms1.getMixture(0) == ms.getMixture(0), __LINE__);
            test (ms1.getMixture(1) == ms.getMixture(1), __LINE__);

            remove(file.c_str());
            
            // Raw
            c.setParam("saveMixtureServerFileFormat", "RAW");
            MixtureServerFileWriter w1(fileRaw, c);
            w1.writeMixtureServer(ms);

            MixtureServerFileReaderRaw r1(fileRaw, c);
            r1.readMixtureServer(ms1);
            test (ms1.getServerName() == ms.getServerName(), __LINE__);
            test (ms1.getDistribCount() == ms.getDistribCount(), __LINE__);
            test (ms1.getMixtureCount() == ms.getMixtureCount(), __LINE__);
            test (ms1.getDistrib(0) == ms.getDistrib(0), __LINE__);
            test (ms1.getDistrib(1) == ms.getDistrib(1), __LINE__);
            test (ms1.getDistrib(2) == ms.getDistrib(2), __LINE__);
            test (ms1.getMixture(0) == ms.getMixture(0), __LINE__);
            test (ms1.getMixture(1) == ms.getMixture(1), __LINE__);

            remove(fileRaw.c_str());

        }

    } // local objects are deleted here 

    return endTest();
}
//-------------------------------------------------------------------------
String TestMixtureServerFileWriter::getClassName() const
{ return "TestMixtureServerFileWriter"; }
//-------------------------------------------------------------------------
TestMixtureServerFileWriter::~TestMixtureServerFileWriter() {}
//-------------------------------------------------------------------------

#endif // !defined(ALIZE_TestMixtureServerFileWriter_cpp)