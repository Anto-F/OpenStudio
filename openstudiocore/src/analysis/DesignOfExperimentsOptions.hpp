/**********************************************************************
 *  Copyright (c) 2008-2015, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#ifndef ANALYSIS_DESIGNOFEXPERIMENTSOPTIONS_HPP
#define ANALYSIS_DESIGNOFEXPERIMENTSOPTIONS_HPP

#include <boost/optional/optional.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/comparison/not_equal.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/auto_rec.hpp>
#include <boost/preprocessor/logical/bool.hpp>
#include <boost/preprocessor/logical/compl.hpp>
#include <boost/preprocessor/repetition/detail/for.hpp>
#include <boost/preprocessor/repetition/for.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../utilities/core/Enum.hpp"
#include "AlgorithmOptions.hpp"
#include "AnalysisAPI.hpp"
#include "analysis/../utilities/core/EnumBase.hpp"
#include "analysis/../utilities/core/LogMessage.hpp"
#include "analysis/../utilities/core/Logger.hpp"

namespace openstudio {
class Attribute;
}  // namespace openstudio

namespace openstudio {
namespace analysis {

namespace detail {

  class DesignOfExperimentsOptions_Impl;

} // detail

/** \class DesignOfExperimentsType 
 *
 *  \relates DesignOfExperimentsOptions */
OPENSTUDIO_ENUM( DesignOfExperimentsType,
  ((FullFactorial)(full factorial))
);

/** DesignOfExperimentsOptions is an AlgorithmOptions class for use with DesignOfExperiments.
 *  \relates DesignOfExperiments */
class ANALYSIS_API DesignOfExperimentsOptions : public AlgorithmOptions {
 public:
  /** @name Constructors and Destructors */
  //@{

  explicit DesignOfExperimentsOptions(const DesignOfExperimentsType& designType);

  /** Constructor provided for deserialization; not for general use. */
  DesignOfExperimentsOptions(const DesignOfExperimentsType& designType,
                             const std::vector<Attribute>& options);

  virtual ~DesignOfExperimentsOptions() {}

  //@}
  /** @name Getters and Queries */
  //@{

  DesignOfExperimentsType designType() const;

  //@}
  /** @name Setters */
  //@{

  void setDesignType(const DesignOfExperimentsType& designType);

  //@}
 protected:
  /// @cond
  typedef detail::DesignOfExperimentsOptions_Impl ImplType;

  explicit DesignOfExperimentsOptions(std::shared_ptr<detail::DesignOfExperimentsOptions_Impl> impl);

  friend class detail::DesignOfExperimentsOptions_Impl;
  friend class AlgorithmOptions;
  /// @endcond
 private:

  REGISTER_LOGGER("openstudio.analysis.DesignOfExperimentsOptions");
};

/** \relates DesignOfExperimentsOptions*/
typedef boost::optional<DesignOfExperimentsOptions> OptionalDesignOfExperimentsOptions;

/** \relates DesignOfExperimentsOptions*/
typedef std::vector<DesignOfExperimentsOptions> DesignOfExperimentsOptionsVector;

} // analysis
} // openstudio

#endif // ANALYSIS_DESIGNOFEXPERIMENTSOPTIONS_HPP

