/*
 * This file is part of Krita
 *
 * Copyright (c) 2016 Spencer Brown <sbrown655@gmail.com>
 * Copyright (c) 2020 Deif Lou <ginoba@gmail.com>
 * 
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef KIS_GRADIENT_MAP_FILTER_H
#define KIS_GRADIENT_MAP_FILTER_H

#include <QObject>

#include <filter/kis_filter.h>
#include <kis_filter_configuration.h>

#include "KisGradientMapFilterConfiguration.h"

class KisConfigWidget;

class KritaGradientMap : public QObject
{
    Q_OBJECT
public:
    KritaGradientMap(QObject *parent, const QVariantList &);
    ~KritaGradientMap() override;
};

class KisGradientMapFilter : public KisFilter
{
public:
    enum ColorMode {
        Blend,
        Nearest,
        Dither,
    };

    KisGradientMapFilter();

    static inline KoID id() {
        return KoID("gradientmap", i18n("Gradient Map"));
    }

    void processImpl(KisPaintDeviceSP device,
                     const QRect& applyRect,
                     const KisFilterConfigurationSP config,
                     KoUpdater *progressUpdater) const override;

    template <typename ColorModeStrategy>
    void processImpl(KisPaintDeviceSP device,
                     const QRect& applyRect,
                     const KisFilterConfigurationSP config,
                     KoUpdater *progressUpdater,
                     const ColorModeStrategy &colorModeStrategy) const;

    KisFilterConfigurationSP factoryConfiguration() const override;
    KisFilterConfigurationSP defaultConfiguration() const override;
    KisConfigWidget* createConfigurationWidget(QWidget* parent, const KisPaintDeviceSP dev, bool useForMasks) const override;
};

#endif