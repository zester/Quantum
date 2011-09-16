/*
 * Copyright (C) 2008-2011 The QXmpp developers
 *
 * Author:
 *  Alex Ermolov
 *
 * Source:
 *  http://code.google.com/p/qxmpp
 *
 * This file is a part of QXmpp library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */

#ifndef QXMPPACTIVITYITEM_H
#define QXMPPACTIVITYITEM_H

#include "QXmppIq.h"

/// \brief The QXmppActivityItem class represents an IQ used for representing
/// UserActivity as defined by XEP-0108.
///
/// \ingroup Stanzas

class QXmppActivityItem : public QXmppIq
{
public:
    /// This enum is used to describe a general activity  type.
    enum General {
        GeneralEmpty = -1,
        DoingChores,
        Drinking,
        Eating,
        Exercising,
        Grooming,
        HavingAppointment,
        Inactive,
        Relaxing,
        Talking,
        Traveling,
        Working
    };
    /// This enum is used to describe a specific activity  type.
    enum Specific {
        SpecificEmpty = -1,
        BuyingGroceries,
        Cleaning,
        Cooking,
        DoingMaintenance,
        DoingTheDishes,
        DoingTheLaundry,
        Gardening,
        RunningAnErrand,
        WalkingTheDog,
        HavingABeer,
        HavingCoffee,
        HavingTea,
        HavingASnack,
        HavingBreakfast,
        HavingDinner,
        HavingLunch,
        Dancing,
        Hiking,
        Jogging,
        PlayingSports,
        Running,
        Skiing,
        Swimming,
        WorkingOut,
        AtTheSpa,
        BrushingTeeth,
        GettingAHaircut,
        Shaving,
        TakingABath,
        TakingAShower,
        DayOff,
        HangingOut,
        Hiding,
        OnVacation,
        Praying,
        ScheduledHoliday,
        Sleeping,
        Thinking,
        Fishing,
        Gaming,
        GoingOut,
        Partying,
        Reading,
        Rehearsing,
        Shopping,
        Smoking,
        Socializing,
        Sunbathing,
        WatchingTv,
        WatchingAMovie,
        InRealLife,
        OnThePhone,
        OnVideoPhone,
        Commuting,
        Cycling,
        Driving,
        InACar,
        OnABus,
        OnAPlane,
        OnATrain,
        OnATrip,
        Walking,
        Coding,
        InAMeeting,
        Studying,
        Writing,
        Other // any other activity (without further specification) not defined herein
    };

    QXmppActivityItem();

    QXmppActivityItem::General activityGeneral() const;
    void setActivityGeneral(General general);

    QXmppActivityItem::Specific activitySpecific() const;
    void setActivitySpecific(Specific specific);

    QString additionalSpecific() const;
    void setAdditionalSpecific(const QString&);

    QString additionalSpecificNS() const;
    void setAdditionalSpecificNS(const QString&);

    QString activityDetailed() const;
    void setActivityDetailed(const QString&);

    QString activityDetailedNS() const;
    void setActivityDetailedNS(const QString&);

    QString text() const;
    void setText(const QString&);

    QString lang() const;
    void setLang(const QString&);

    /// \cond
    bool isStop() const;
    bool isAdditionalSpecific() const;
    bool isDetailed() const;

    static bool isActivityItem(const QDomElement &element);

    void parse(const QDomElement &activity);
    void toXml(QXmlStreamWriter *writer) const;
    /// \endcond

private:
    General m_actgen;
    Specific m_actspec;
    QString m_specadd;
    QString m_specaddns;
    QString m_detailed;
    QString m_detailedns;
    QString m_text;
    QString m_lang;
    bool m_bstop;
    bool m_bspecadd;
    bool m_bdetailed;
};

#endif
