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

#if !defined(ALIZE_FeatureFileReaderSPro4_h)
#define ALIZE_FeatureFileReaderSPro4_h

#ifdef WIN32
#ifdef ALIZE_EXPORTS
#define ALIZE_API __declspec(dllexport)
#else
#define ALIZE_API __declspec(dllimport)
#endif
#else
#define ALIZE_API
#endif

#include "FeatureFileReaderSingle.h"
#include "RealVector.h"


namespace alize
{
  class LabelServer;
  class Config;
  class FileReader;

  /// Convenient class for reading features from a S-PRO 4 file
  /// The file is opened only after calling one of the methods readFeature,
  /// get FeatureCount, getVectSize, getFeatureFlags
  ///
  /// @author Frederic Wils  frederic.wils@lia.univ-avignon.fr
  /// @version 1.0
  /// @date 2003

  class ALIZE_API FeatureFileReaderSPro4 : public FeatureFileReaderSingle
  {
    friend class TestFeatureFileReaderSPro4;

  public :

    /// Creates a reader for a SPro 4.x feature file.
    /// @param f a file to read. No path is
    ///    required. It uses the parameter "featureFilesPath" of the
    ///    configuration.
    /// @param c the configuration to use
    /// @param ls address of a label server. can be NULL.
    /// @param be big endian ? Can be BIGENDIAN_AUTO, BIGENDIAN_TRUE or
    ///        BIGENDIAN_FALSE
    ///
    FeatureFileReaderSPro4(const FileName& f,
       const Config& c, LabelServer* ls = NULL, BigEndian = BIGENDIAN_AUTO,
       BufferUsage b = BUFFER_AUTO, unsigned long bufferSize = 0,
       HistoricUsage = ALL_FEATURES, unsigned long historicSize = 0);
    
    /// See constructor with same parameters
    ///
    static FeatureFileReaderSPro4& create(const FileName&, const Config& c,
       LabelServer* ls = NULL, BigEndian = BIGENDIAN_AUTO,
       BufferUsage b = BUFFER_AUTO, unsigned long bufferSize = 0,
       HistoricUsage = ALL_FEATURES, unsigned long historicSize = 0);

    virtual ~FeatureFileReaderSPro4();

    /// Returns the number of features in the file
    /// @return the number of features in the file
    /// @exception IOException if an I/O error occurs
    /// @exception FileNotFoundException
    /// @exception InvalidDataException thrown if the file is not a valid
    ///      SPro file
    ///
    virtual unsigned long getFeatureCount();

    /// Returns the size of the vector inside the features of this file
    /// @return the size of the vector inside the features of this file
    /// @exception IOException if an I/O error occurs
    /// @exception FileNotFoundException
    /// @exception InvalidDataException thrown if the file is not a valid
    ///      SPro file
    ///
    virtual unsigned long getVectSize();

    /// Returns the feature flags of this file
    /// @return the feature flags of this file
    /// @exception IOException if an I/O error occurs
    /// @exception FileNotFoundException
    /// @exception InvalidDataException thrown if the file is not a valid
    ///      SPro file
    ///
    virtual const FeatureFlags& getFeatureFlags();

    /// Returns the sample rate of this file.
    /// @return the sample rate of this file
    /// @exception IOException if an I/O error occurs
    /// @exception FileNotFoundException
    /// @exception InvalidDataException thrown if the file is not a valid
    ///      SPro file
    ///
    virtual real_t getSampleRate();

    virtual String getClassName() const;

  private :

    bool _paramDefined;
    void readParams();
    bool readHeader();
    virtual unsigned long getHeaderLength();

    bool operator==(const FeatureFileReaderSPro4&)
                         const; /*!Not implemented*/
    bool operator!=(const FeatureFileReaderSPro4&)
                         const; /*!Not implemented*/
    const FeatureFileReaderSPro4& operator=(
             const FeatureFileReaderSPro4&); /*!Not implemented*/
    FeatureFileReaderSPro4(
             const FeatureFileReaderSPro4&); /*!Not implemented*/
  };

} // end namespace alize

#endif // !defined(ALIZE_FeatureFileReaderSPro4_h)

