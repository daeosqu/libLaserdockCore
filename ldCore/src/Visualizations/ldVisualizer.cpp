/**
    libLaserdockCore
    Copyright(c) 2018 Wicked Lasers

    This file is part of libLaserdockCore.

    libLaserdockCore is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libLaserdockCore is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libLaserdockCore.  If not, see <https://www.gnu.org/licenses/>.
**/

#include "ldCore/Visualizations/ldVisualizer.h"

#include "ldCore/ldCore.h"
#include "ldCore/Visualizations/MusicManager/ldMusicManager.h"
#include "ldCore/Visualizations/ldVisualizationTask.h"

/*!
 * \class ldVisualizer
 * \inmodule Laserdock Project
 * \brief ldVisualizer is a self-contained unit of visualization, to be ran by ldVisualizationTask.
 */

/*!
 * \fn ldVisualizer::ldVisualizer()
 * \brief ldVisualizer::ldVisualizer
 */
ldVisualizer::ldVisualizer(QObject *parent)
    : QObject(parent)
{
    m_musicManager = ldCore::instance()->musicManager();

    setContentSize(CCSize(2, 2));
    setAnchorPoint(CCPoint(0.5, 0.5));
}

/*!
 * ldVisualizer::~ldVisualizer()
 * \brief ldVisualizer::~ldVisualizer
 */
ldVisualizer::~ldVisualizer()
{
}

/*!
 * \fn virtual const char* ldVisualizer::visualizerName()
 * \brief Gets the name of visualizer.
 * Override in subclasses & fill in the empty string with a name of the visualizer.
 * Returns the name of visualizer as \c char* format.
 */
QString ldVisualizer::visualizerName() const
{
    return "";
}

void ldVisualizer::start() {
    // set local rate if available
    if(m_rate != 0) {
        m_renderer->setRate(m_rate);
    } else {
         // having this will prevent renderer rate being out of sync if a user
         // creates a visualizer and incorrectly uses m_renderer->setRate() instead of correctly
         // setting m_rate in the class init.
         m_renderer->setRate(ldAbstractRenderer::DEFAULT_RATE);
    }

    // set default quality values because some old visualizers don't do it
    // good practice is to set quality params in onShouldStart()
    m_renderer->setRenderParamsQuality();

    onShouldStart();

    m_isVisActive = true;
    m_isVisPaused = false;
}

void ldVisualizer::pause()
{
    onShouldPause();

    m_isVisPaused = true;
}

void ldVisualizer::stop() {
    onShouldStop();

    m_isVisActive = false;
    m_isVisPaused = false;

    // restore global rate
    if(m_rate != 0) {
        m_renderer->setRate(ldAbstractRenderer::DEFAULT_RATE);
    }

}

/*!
 * \fn void ldVisualizer::onShouldStart()
 * \brief This method is called to prepare the visualizer before running.
 * This method is called by the ldVisualizationTask to prepare the visualizer for running.
 * Usually it sets up LibOL parameters appropriate for this visualizer.
 */
void ldVisualizer::onShouldStart()
{
}

void ldVisualizer::onShouldPause()
{

}

/*!
 * \fn void ldVisualizer::onShouldStop()
 * \brief This method is called to stop any activity in the visualizer
 * This method is called by the ldVisualizationTask to stop the visualizer activity.
 */
void ldVisualizer::onShouldStop()
{
}

/*!
 * \fn void ldVisualizer::updateWith(float delta)
 * \brief This method is called by ldVisualizationTask::onUpdate to updates the visualizer with the pointer to currently playing ldSoundMusic object.
 * The parameter \a delta is a dealy time.
 */
void ldVisualizer::updateWith(ldSoundData *pSoundData, float delta)
{
    if (pSoundData == NULL)
    {
        clearBuffer();
        return;
    }

    onUpdate(pSoundData, delta);
}

bool ldVisualizer::isVisActive() const
{
    return m_isVisActive;
}

bool ldVisualizer::isVisPaused() const
{
    return m_isVisPaused;
}

void ldVisualizer::draw()
{
}


