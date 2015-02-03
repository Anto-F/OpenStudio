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

#include <boost/none.hpp>
#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_Schedule_Compact_FieldEnums.hxx>
#include <utilities/idd/Schedule_Compact_FieldEnums.hxx>

#include "../../model/ScheduleCompact.hpp"
#include "../../utilities/idd/IddEnums.hpp"
#include "../../utilities/idf/IdfExtensibleGroup.hpp"
#include "../ReverseTranslator.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/EnumBase.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/LogMessage.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/Logger.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/../core/Optional.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idd/IddObject.hpp"
#include "energyplus/ReverseTranslator/../../model/../utilities/idf/WorkspaceObject.hpp"
#include "energyplus/ReverseTranslator/../../model/ModelObject.hpp"

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

OptionalModelObject ReverseTranslator::translateScheduleCompact( const WorkspaceObject & workspaceObject )
{
  if( workspaceObject.iddObject().type() != IddObjectType::Schedule_Compact )
  {
    LOG(Error, "WorkspaceObject is not IddObjectType: Schedule:Compact");
    return boost::none;
  }

  ScheduleCompact scheduleCompact(m_model);

  OptionalWorkspaceObject target = workspaceObject.getTarget(Schedule_CompactFields::ScheduleTypeLimitsName);
  if (target){
    OptionalModelObject scheduleTypeLimits = translateAndMapWorkspaceObject(*target);
    if (scheduleTypeLimits){
      scheduleCompact.setPointer(OS_Schedule_CompactFields::ScheduleTypeLimitsName, scheduleTypeLimits->handle());
    }
  }

  if (OptionalString os = workspaceObject.name()) {
    scheduleCompact.setName(*os);
  }

  for (const IdfExtensibleGroup& eg : workspaceObject.extensibleGroups()) {
    scheduleCompact.pushExtensibleGroup(eg.fields());
  }

  return scheduleCompact;
}

} // energyplus

} // openstudio

