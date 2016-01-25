/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.  
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

#ifndef OPENSTUDIO_SPACETYPESCONTROLLER_HPP
#define OPENSTUDIO_SPACETYPESCONTROLLER_HPP

#include "ModelSubTabController.hpp"

namespace openstudio {

class SpaceTypesController : public ModelSubTabController
{
  Q_OBJECT

  public:

    SpaceTypesController(bool isIP, 
      const model::Model & model);

    virtual ~SpaceTypesController() {}

  protected:

    virtual void onAddObject(const openstudio::IddObjectType& iddObjectType) override;

    virtual void onAddObject(const openstudio::model::ModelObject& modelObject) override;

    virtual void onCopyObject(const openstudio::model::ModelObject& modelObject) override;

    virtual void onRemoveObject(openstudio::model::ModelObject) override;

    virtual void onReplaceObject(openstudio::model::ModelObject modelObject, const OSItemId& replacementItemId) override;

    virtual void onPurgeObjects(const openstudio::IddObjectType& iddObjectType) override;

    virtual void onDrop(const OSItemId& itemId) override;

    virtual void onInspectItem(OSItem* item) override;
};

} // openstudio

#endif // OPENSTUDIO_SPACETYPESCONTROLLER_HPP
