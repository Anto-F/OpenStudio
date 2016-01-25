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

#ifndef MODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_IMPL_HPP
#define MODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_IMPL_HPP

#include "ModelAPI.hpp"
#include "StraightComponent_Impl.hpp"

namespace openstudio {
namespace model {

class Schedule;

namespace detail {

  /** AirTerminalSingleDuctVAVNoReheat_Impl is a StraightComponent_Impl that is the implementation class for AirTerminalSingleDuctVAVNoReheat.*/
  class MODEL_API AirTerminalSingleDuctVAVNoReheat_Impl : public StraightComponent_Impl {
    Q_OBJECT;

    Q_PROPERTY(boost::optional<double> maximumAirFlowRate READ maximumAirFlowRate WRITE setMaximumAirFlowRate RESET resetMaximumAirFlowRate);
    Q_PROPERTY(bool isMaximumAirFlowRateAutosized READ isMaximumAirFlowRateAutosized);

    Q_PROPERTY(boost::optional<std::string> zoneMinimumAirFlowInputMethod READ zoneMinimumAirFlowInputMethod WRITE setZoneMinimumAirFlowInputMethod RESET resetZoneMinimumAirFlowInputMethod);
    Q_PROPERTY(std::vector<std::string> zoneMinimumAirFlowInputMethodValues READ zoneMinimumAirFlowInputMethodValues);

    Q_PROPERTY(boost::optional<double> constantMinimumAirFlowFraction READ constantMinimumAirFlowFraction WRITE setConstantMinimumAirFlowFraction RESET resetConstantMinimumAirFlowFraction);

    Q_PROPERTY(boost::optional<double> fixedMinimumAirFlowRate READ fixedMinimumAirFlowRate WRITE setFixedMinimumAirFlowRate RESET resetFixedMinimumAirFlowRate);

    Q_PROPERTY(boost::optional<openstudio::model::ModelObject> availabilitySchedule READ availabilityScheduleAsModelObject WRITE setAvailabilityScheduleAsModelObject);
    Q_PROPERTY(boost::optional<openstudio::model::ModelObject> minimumAirFlowFractionSchedule READ minimumAirFlowFractionScheduleAsModelObject WRITE setMinimumAirFlowFractionScheduleAsModelObject RESET resetMinimumAirFlowFractionSchedule);
   public:
    /** @name Constructors and Destructors */
    //@{

    AirTerminalSingleDuctVAVNoReheat_Impl(const IdfObject& idfObject,
                                          Model_Impl* model,
                                          bool keepHandle);

    AirTerminalSingleDuctVAVNoReheat_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                          Model_Impl* model,
                                          bool keepHandle);

    AirTerminalSingleDuctVAVNoReheat_Impl(const AirTerminalSingleDuctVAVNoReheat_Impl& other,
                                          Model_Impl* model,
                                          bool keepHandle);

    virtual ~AirTerminalSingleDuctVAVNoReheat_Impl() {}

    //@}

    /** @name Virtual Methods */
    //@{

    virtual const std::vector<std::string>& outputVariableNames() const override;

    virtual IddObjectType iddObjectType() const override;

    virtual std::vector<ScheduleTypeKey> getScheduleTypeKeys(const Schedule& schedule) const override;

    virtual unsigned inletPort() override;

    virtual unsigned outletPort() override;

    virtual bool addToNode(Node& node) override;

    virtual std::vector<openstudio::IdfObject> remove() override;

    virtual bool isRemovable() const override;

    //@}
    /** @name Getters */
    //@{

    // TODO: Check return type. From object lists, some candidates are: Schedule.
    Schedule availabilitySchedule() const;

    boost::optional<double> maximumAirFlowRate() const;

    bool isMaximumAirFlowRateAutosized() const;

    boost::optional<std::string> zoneMinimumAirFlowInputMethod() const;

    boost::optional<double> constantMinimumAirFlowFraction() const;

    bool isConstantMinimumAirFlowFractionDefaulted() const;

    boost::optional<double> fixedMinimumAirFlowRate() const;

    bool isFixedMinimumAirFlowRateDefaulted() const;

    // TODO: Check return type. From object lists, some candidates are: Schedule.
    boost::optional<Schedule> minimumAirFlowFractionSchedule() const;

    //@}
    /** @name Setters */
    //@{

    // TODO: Check argument type. From object lists, some candidates are: Schedule.
    bool setAvailabilitySchedule(Schedule& schedule);

    bool setMaximumAirFlowRate(boost::optional<double> maximumAirFlowRate);

    void resetMaximumAirFlowRate();

    void autosizeMaximumAirFlowRate();

    bool setZoneMinimumAirFlowInputMethod(boost::optional<std::string> zoneMinimumAirFlowInputMethod);

    void resetZoneMinimumAirFlowInputMethod();

    bool setConstantMinimumAirFlowFraction(boost::optional<double> constantMinimumAirFlowFraction);

    void resetConstantMinimumAirFlowFraction();

    bool setFixedMinimumAirFlowRate(boost::optional<double> fixedMinimumAirFlowRate);

    void resetFixedMinimumAirFlowRate();

    bool setMinimumAirFlowFractionSchedule(Schedule& schedule);

    void resetMinimumAirFlowFractionSchedule();

    bool controlForOutdoorAir() const;

    void setControlForOutdoorAir(bool controlForOutdoorAir);

    //@}
    /** @name Other */
    //@{

    //@}
   protected:
   private:
    REGISTER_LOGGER("openstudio.model.AirTerminalSingleDuctVAVNoReheat");

    // Optional getters for use by methods like children() so can remove() if the constructor fails.
    // There are other ways for the public versions of these getters to fail--perhaps all required
    // objects should be returned as boost::optionals
    boost::optional<Schedule> optionalAvailabilitySchedule() const;

    std::vector<std::string> zoneMinimumAirFlowInputMethodValues() const;

    boost::optional<ModelObject> availabilityScheduleAsModelObject() const;
    boost::optional<ModelObject> minimumAirFlowFractionScheduleAsModelObject() const;

    bool setAvailabilityScheduleAsModelObject(const boost::optional<ModelObject>& modelObject);
    bool setMinimumAirFlowFractionScheduleAsModelObject(const boost::optional<ModelObject>& modelObject);
  };

} // detail

} // model
} // openstudio

#endif // MODEL_AIRTERMINALSINGLEDUCTVAVNOREHEAT_IMPL_HPP

