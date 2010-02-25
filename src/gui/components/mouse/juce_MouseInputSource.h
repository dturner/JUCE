/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-9 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_MOUSEEVENT_JUCEHEADER__x
#define __JUCE_MOUSEEVENT_JUCEHEADER__x

class Component;
class ComponentPeer;
class MouseInputSourceInternal;
#include "../keyboard/juce_ModifierKeys.h"
#include "../../../core/juce_Time.h"
#include "../../../containers/juce_ScopedPointer.h"
#include "../../graphics/geometry/juce_Point.h"
#include "../juce_Desktop.h"


//==============================================================================
/**
    Represents a linear source of mouse events from a mouse device or individual finger
    in a multi-touch environment.

    Each MouseEvent object contains a reference to the MouseInputSource that generated
    it. In an environment with a single mouse for input, all events will come from the
    same source, but in a multi-touch system, there may be multiple MouseInputSource
    obects active, each representing a stream of events coming from a particular finger.

    Events coming from a single MouseInputSource are always sent in a fixed and predictable
    order: a mouseMove will never be called without a mouseEnter having been sent beforehand,
    the only events that can happen between a mouseDown and its corresponding mouseUp are
    mouseDrags, etc.
    When there are multiple touches arriving from multiple MouseInputSources, their
    event streams may arrive in an interleaved order, so you should use the getIndex()
    method to find out which finger each event came from.

    @see MouseEvent
*/
class JUCE_API  MouseInputSource
{
public:
    //==============================================================================
    /** Creates a MouseInputSource.
        You should never actually create a MouseInputSource in your own code - the
        library takes care of managing these objects.
    */
    MouseInputSource (int index, bool isMouseDevice);

    /** Destructor. */
    ~MouseInputSource();

    //==============================================================================
    /** Returns true if this object represents a normal desk-based mouse device. */
    bool isMouse() const;

    /** Returns true if this object represents a source of touch events - i.e. a finger or stylus. */
    bool isTouch() const;

    /** Returns true if this source has an on-screen pointer that can hover over
        items without clicking them.
    */
    bool canHover() const;

    /** Returns true if this source may have a scroll wheel. */
    bool hasMouseWheel() const;

    /** Returns this source's index in the global list of possible sources.
        If the system only has a single mouse, there will only be a single MouseInputSource
        with an index of 0.

        If the system supports multi-touch input, then the index will represent a finger
        number, starting from 0. When the first touch event begins, it will have finger
        number 0, and then if a second touch happens while the first is still down, it
        will have index 1, etc.
    */
    int getIndex() const;

    /** Returns true if this device is currently being pressed. */
    bool isDragging() const;

    /** Returns the last-known screen position of this source. */
    const Point<int> getScreenPosition() const;

    /** Returns a set of modifiers that indicate which buttons are currently
        held down on this device.
    */
    const ModifierKeys getCurrentModifiers() const;

    /** Returns the component that was last known to be under this pointer. */
    Component* getComponentUnderMouse() const;

    /** Tells the device to dispatch a mouse-move event.
        This is asynchronous - the event will occur on the message thread.
    */
    void triggerFakeMove() const;

    /** Returns the number of clicks that should be counted as belonging to the
        current mouse event.
        So the mouse is currently down and it's the second click of a double-click, this
        will return 2.
    */
    int getNumberOfMultipleClicks() const throw();

    /** Returns the time at which the last mouse-down occurred. */
    const Time getLastMouseDownTime() const throw();

    /** Returns the screen position at which the last mouse-down occurred. */
    const Point<int> getLastMouseDownPosition() const throw();

    /** Returns true if this mouse is currently down, and if it has been dragged more
        than a couple of pixels from the place it was pressed.
    */
    bool hasMouseMovedSignificantlySincePressed() const throw();

    bool hasMouseCursor() const throw();
    void showMouseCursor (const MouseCursor& cursor);
    void hideCursor();
    void revealCursor();

    bool canDoUnboundedMovement() const throw();

    /** Allows the mouse to move beyond the edges of the screen.

        Calling this method when the mouse button is currently pressed will remove the cursor
        from the screen and allow the mouse to (seem to) move beyond the edges of the screen.

        This means that the co-ordinates returned to mouseDrag() will be unbounded, and this
        can be used for things like custom slider controls or dragging objects around, where
        movement would be otherwise be limited by the mouse hitting the edges of the screen.

        The unbounded mode is automatically turned off when the mouse button is released, or
        it can be turned off explicitly by calling this method again.

        @param shouldUnboundedMovementBeEnabled     whether to turn this mode on or off
        @param keepCursorVisibleUntilOffscreen      if set to false, the cursor will immediately be
                                                    hidden; if true, it will only be hidden when it
                                                    is moved beyond the edge of the screen
    */
    void enableUnboundedMouseMovement (bool isEnabled, bool keepCursorVisibleUntilOffscreen = false);

    //==============================================================================
    juce_UseDebuggingNewOperator

    /** @internal */
    void handleEvent (ComponentPeer* peer, const Point<int>& positionWithinPeer, int64 time, const ModifierKeys& mods);
    /** @internal */
    void handleWheel (ComponentPeer* peer, const Point<int>& positionWithinPeer, int64 time, float x, float y);

private:
    friend class Desktop;
    friend class ComponentPeer;
    friend class MouseInputSourceInternal;
    ScopedPointer<MouseInputSourceInternal> pimpl;

    MouseInputSource (const MouseInputSource&);
    MouseInputSource& operator= (const MouseInputSource&);
};


#endif   // __JUCE_MOUSEEVENT_JUCEHEADER__
