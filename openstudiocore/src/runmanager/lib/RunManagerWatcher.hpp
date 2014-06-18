/**********************************************************************
 *  Copyright (c) 2008-2014, Alliance for Sustainable Energy.
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

#ifndef RUNMANAGER_LIB_RUNMANAGERWATCHER_HPP
#define RUNMANAGER_LIB_RUNMANAGERWATCHER_HPP

#include "RunManagerAPI.hpp"

#include <vector>
#include <string>
#include <QObject>
#include "../../utilities/core/UUID.hpp"
#include "RunManager.hpp"
#include "Job.hpp"

namespace openstudio {
  class DateTime;

namespace runmanager {
  class RUNMANAGER_API RunManagerWatcher : public QObject
  {
    Q_OBJECT;
    REGISTER_LOGGER("openstudio.runmanager.RunManagerWatcher");

    public:
      RunManagerWatcher(const RunManager &t_runManager);
      virtual ~RunManagerWatcher() {}

    protected:
      virtual void jobStarted(const openstudio::UUID &t_id) {}
      virtual void jobFinished(const openstudio::UUID &id, const openstudio::runmanager::JobErrors& errors) {}
      virtual void jobFinishedExt(const openstudio::UUID &id, const openstudio::runmanager::JobErrors& errors, 
          const openstudio::DateTime &lastRun, const std::vector<openstudio::runmanager::FileInfo> &outputfiles) {}
      virtual void jobOutputFileChanged(const openstudio::UUID &id, const openstudio::runmanager::FileInfo& file) {}
      virtual void jobStateChanged(const openstudio::UUID &id) {}
      virtual void jobOutputDataAdded(const openstudio::UUID &id, const std::string &data) {}
      virtual void jobStatusChanged(const openstudio::runmanager::AdvancedStatus &status) {}
      virtual void jobChildrenChanged(const openstudio::UUID &id) {}
      virtual void jobParentChanged(const openstudio::UUID &id) {}
      virtual void jobTreeChanged(const openstudio::UUID &id) {}
      virtual void jobUuidChanged(const openstudio::UUID &t_oldUUID, const openstudio::UUID &t_newUUID) {}

      virtual void runManagerPausedChanged(bool) {}
      virtual void runManagerStatsChanged() {}
      virtual void runManagerJobTreeAdded(const openstudio::runmanager::Job &t_job) {}

      /// Called once for each job that was completed. Merged jobs are automatically split out
      /// into separate calls, executed in the order the jobs were run
      ///
      /// \param[in] t_jobId UUID of the job that finished
      /// \param[in] t_jobType JobType of the job that finished
      /// \param[in] t_lastRun DateTime time that the job completed. Note that
      ///                      multiple jobs will have the exact same last run time
      ///                      if they were merged for optimization
      /// \param[in] t_errors Error and results from the job execution
      /// \param[in] t_outputFiles Files generated by the job
      /// \param[in] t_inputParams JobParams used to create the job. This can be helpful for passing to RubyJobCreator.
      /// \param[in] t_isMergedJob true if the job was merged into another job for optimization before execution
      /// \param[in] t_mergedIntoJobId The UUID of the job that this job was merged into
      virtual void jobFinishedDetails(
          const openstudio::UUID &t_jobId, 
          const openstudio::runmanager::JobType &t_jobType,
          const openstudio::DateTime &t_lastRun,
          const openstudio::runmanager::JobErrors &t_errors,
          const openstudio::runmanager::Files &t_outputFiles,
          const openstudio::runmanager::JobParams &t_inputParams, 
          bool t_isMergedJob,
          const openstudio::UUID &t_mergedIntoJobId) {}

      /// Called once for each job tree that has completed
      virtual void treeFinished(const openstudio::runmanager::Job &t_job)
      { }

      Job getJob(const openstudio::UUID &t_uuid);

    private:
      void hookUpSignals(const openstudio::runmanager::Job &t_job);
      void runManagerJobTreeAddedInternal(const openstudio::runmanager::Job &t_job);
      void jobFinishedExtInternal(const openstudio::UUID &id, const openstudio::runmanager::JobErrors& errors, 
          const openstudio::DateTime &lastRun, const std::vector<openstudio::runmanager::FileInfo> &outputfiles);

      RunManager m_runManager;

    private slots:
      /// Emitted after the job has started
      void started(const openstudio::UUID &id);

      /// Emitted after the job has finished
      void finished(const openstudio::UUID &id, const openstudio::runmanager::JobErrors& errors);

      /// Emitted after the job has finished
      void finishedExt(const openstudio::UUID &id, const openstudio::runmanager::JobErrors& errors, 
          const openstudio::DateTime &lastRun, const std::vector<openstudio::runmanager::FileInfo> &outputfiles);

      /// Emitted after generated output file has changed.
      void outputFileChanged(const openstudio::UUID &id, const openstudio::runmanager::FileInfo& file);

      /// Emitted after the state (runnable/canceled/outofdate) or index of a job has changed
      void stateChanged(const openstudio::UUID &id);

      /// Emitted after any data has been sent to stdout from the job, does not wait for
      /// complete lines
      void outputDataAdded(const openstudio::UUID &id, const std::string &data);

      /// Emitted after new detailed status information becomes available
      void statusChanged(const openstudio::runmanager::AdvancedStatus &status);

      /// Emitted after the list of children or the finished job child changes
      void childrenChanged(const openstudio::UUID &id);

      /// Emitted after the the parent of this job changes
      void parentChanged(const openstudio::UUID &id);

      /// Emitted whenever this state of this job tree (this job and any child) changes
      void treeChanged(const openstudio::UUID &id);


      /// Emitted when a Job's UUID has changed via a updateJob() call
      void uuidChanged(const openstudio::UUID &t_oldUUID, const openstudio::UUID &t_newUUID);


      /// Emitted when the paused state has change
      void pausedChanged(bool);

      /// Stats changed
      void statsChanged();

      /// Job tree added
      void jobTreeAdded(const openstudio::UUID &t_job);
  };

}
}

#endif // RUNMANAGER_LIB_RUNMANAGERWATCHER_HPP
