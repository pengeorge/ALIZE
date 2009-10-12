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

#if !defined(ALIZE_ConfigChecker_h)
#define ALIZE_ConfigChecker_h

#ifdef WIN32
#ifdef ALIZE_EXPORTS
#define ALIZE_API __declspec(dllexport)
#else
#define ALIZE_API __declspec(dllimport)
#endif
#else
#define ALIZE_API
#endif

#include "alizeString.h"
#include "Object.h"
#include "RefVector.h"

namespace alize
{
  class Config;
  /*!
  Class for validating parameters of a configuration object.
    
  @author Frederic Wils  frederic.wils@lia.univ-avignon.fr
  @version 1.0
  @date 2005
  */
  class ALIZE_API ConfigChecker : public Object
  {
    friend class TestConfigChecker;

  public :

    ConfigChecker();
    virtual ~ConfigChecker();


    /// Checks a configuration
    /// @exception ConfigCheckException thrown if check fail
    /// @param c the config to check
    ///
    void check(const Config& c);

    /// Returns the list of parameters. Useful for --help on command line
    /// @return the list of parameters
    ///
    String getParamList();

    /// Adds an integer parameter
    /// @param name name of the parameter
    /// @param mandatory true if option is mandatory in the config; false otherwise
    /// @param argIsRequired true if argument is mandatory for this option; false otherwise
    /// @param desc description. Useful for --help
    /// @exception Exception  throw if name is empty
    /// 
    void addIntegerParam(const String& name, bool mandatory,
      bool argIsRequired, const String& desc = "");

    /// Adds a float parameter
    /// @param name name of the parameter
    /// @param mandatory true if option is mandatory in the config; false otherwise
    /// @param argIsRequired true if argument is mandatory for this option; false otherwise
    /// @param desc description. Useful for --help
    /// @exception Exception  throw if name is empty
    /// 
    void addFloatParam(const String& name, bool mandatory,
      bool argIsRequired, const String& desc = "");

    /// Adds a boolean parameter
    /// @param name name of the parameter
    /// @param mandatory true if option is mandatory in the config; false otherwise
    /// @param argIsRequired true if argument is mandatory for this option; false otherwise
    /// @param desc description. Useful for --help
    /// @exception Exception  throw if name is empty
    /// 
    void addBooleanParam(const String& name, bool mandatory,
      bool argIsRequired, const String& desc = "");

    /// Adds a string parameter
    /// @param name name of the parameter
    /// @param mandatory true if option is mandatory in the config; false otherwise
    /// @param argIsRequired true if argument is mandatory for this option; false otherwise
    /// @param desc description. Useful for --help
    /// @exception Exception  throw if name is empty
    /// 
    void addStringParam(const String& name, bool mandatory,
      bool argIsRequired, const String& desc = "");

    virtual String getClassName() const;

    /// Internal class. Do not use
    
    class Param : public Object
    {
    public :
      String    name;
      bool      mandatory;
      bool      argIsRequired;
      ParamType type;
      String    description;
      virtual String getClassName() const;
    };

  private :

    RefVector<Param> _vect;

    void err(const String& e) const;
    void checkName(const String& name) const;
    ConfigChecker(const ConfigChecker&);     /*!not implemented*/
    const ConfigChecker& operator=(
                const ConfigChecker& c);/*!not implemented*/
    bool operator==(const ConfigChecker& c) const;/*!not implemented*/
    bool operator!=(const ConfigChecker& c) const;/*!not implemented*/
  };

} // end namespace alize

#endif // !defined(ALIZE_ConfigChecker_h)
