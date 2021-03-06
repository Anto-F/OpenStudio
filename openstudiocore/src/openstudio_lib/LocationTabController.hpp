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

#ifndef OPENSTUDIO_LOCATIONTABCONTROLLER_HPP
#define OPENSTUDIO_LOCATIONTABCONTROLLER_HPP

#include "../model/Model.hpp"

#include "MainTabController.hpp"

#include <boost/smart_ptr.hpp>

#include <QDir>
#include <QObject>

class QStackedWidget;

namespace openstudio {

class LocationTabView;

class UtilityBillsController;

class LocationTabController : public MainTabController
{
  Q_OBJECT

public:

  LocationTabController(bool isIP,
    const model::Model& model,
    const QString& modelTempDir);

  virtual ~LocationTabController();

  enum TabID
  {
    WEATHER_FILE,
    LIFE_CYCLE_COSTS,
    UTILITY_BILLS
  };

private:

  bool showUtilityBills();

  QString m_modelTempDir;

  model::Model m_model;

  bool m_isIP;

  QWidget * m_currentView = nullptr;

  int m_currentIndex = -1;

private slots:

  virtual void setSubTab(int index) override;
 
};

} // openstudio

#endif // OPENSTUDIO_LOCATIONTABCONTROLLER_HPP
