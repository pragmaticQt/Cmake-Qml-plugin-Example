// MIT License
//
// Copyright (c) 2020 Olivier Le Doeuff
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __QATERIAL_ICON_DESCRIPTION_HPP__
#define __QATERIAL_ICON_DESCRIPTION_HPP__

// ──── INCLUDE ────

// Library Headers
#include <Qaterial/Export.hpp>

// Dependencies Headers
#include <QUrl>
#include <QColor>
#include <qqml.h>
// ──── DECLARATION ────

// ──── CLASS ────
namespace qaterial {


class QATERIAL_API_ IconDescription : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl   source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int    width  READ width  WRITE setWidth  NOTIFY widthChanged)
    Q_PROPERTY(int    height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(QColor color  READ color  WRITE setColor  NOTIFY colorChanged)
    Q_PROPERTY(bool   cache  READ cache  WRITE setCache  NOTIFY cacheChanged)

    QML_ELEMENT
    Q_CLASSINFO(CLASSINFO_HEADER, "Qaterial/IconDescription 1.0")

public:
    // ──── CONSTRUCTOR ────
    IconDescription(QObject* parent = nullptr) : QObject(parent) {}

    QUrl   source() const
    {
        return m_source;
    }
    int    width() const
    {
        return m_width;
    }
    int    height() const
    {
        return m_height;
    }
    QColor color() const
    {
        return m_color;
    }
    bool   cache() const
    {
        return m_cache;
    }

public slots:
    void setSource(QUrl source)
    {
        if (m_source == source)
            return;

        m_source = source;
        emit sourceChanged(m_source);
    }
    void setWidth(int width)
    {
        if (m_width == width)
            return;

        m_width = width;
        emit widthChanged(m_width);
    }
    void setHeight(int height)
    {
        if (m_height == height)
            return;

        m_height = height;
        emit heightChanged(m_height);
    }
    void setColor(QColor color)
    {
        if (m_color == color)
            return;

        m_color = color;
        emit colorChanged(m_color);
    }
    void setCache(bool cache)
    {
        if (m_cache == cache)
            return;

        m_cache = cache;
        emit cacheChanged(m_cache);
    }

signals:
    void sourceChanged(QUrl source);
    void widthChanged(int width);
    void heightChanged(int height);
    void colorChanged(QColor color);
    void cacheChanged(bool cache);

private:
    QUrl   m_source;
    int    m_width  = 24;
    int    m_height = 24;
    QColor m_color;
    bool   m_cache  = true;
};

}
#endif
