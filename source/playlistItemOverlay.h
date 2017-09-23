/*  This file is part of YUView - The YUV player with advanced analytics toolset
*   <https://github.com/IENT/YUView>
*   Copyright (C) 2015  Institut für Nachrichtentechnik, RWTH Aachen University, GERMANY
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 3 of the License, or
*   (at your option) any later version.
*
*   In addition, as a special exception, the copyright holders give
*   permission to link the code of portions of this program with the
*   OpenSSL library under certain conditions as described in each
*   individual source file, and distribute linked combinations including
*   the two.
*   
*   You must obey the GNU General Public License in all respects for all
*   of the code used other than OpenSSL. If you modify file(s) with this
*   exception, you may extend this exception to your version of the
*   file(s), but you are not obligated to do so. If you do not wish to do
*   so, delete this exception statement from your version. If you delete
*   this exception statement from all source files in the program, then
*   also delete it here.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PLAYLISTITEMOVERLAY_H
#define PLAYLISTITEMOVERLAY_H

#include "playlistItemContainer.h"
#include "typedef.h"
#include "ui_playlistItemOverlay.h"

class playlistItemOverlay : public playlistItemContainer
{
  Q_OBJECT

public:
  playlistItemOverlay();

  virtual infoData getInfo() const Q_DECL_OVERRIDE;

  virtual QString getPropertiesTitle() const Q_DECL_OVERRIDE { return "Overlay Properties"; }

  // Overload from playlistItemVideo.
  virtual QSize getSize() const Q_DECL_OVERRIDE;

  // Overload from playlistItemVideo. We add some specific drawing functionality if the two
  // children are not comparable.
  virtual void drawItem(QPainter *painter, int frameIdx, double zoomFactor, bool drawRawData) Q_DECL_OVERRIDE;

  // The overlay item itself does not need to load anything. We just pass all of these to the child items.
  virtual itemLoadingState needsLoading(int frameIdx, bool loadRawData) Q_DECL_OVERRIDE;
  virtual void loadFrame(int frameIdx, bool playing, bool loadRawData, bool emitSignals=true) Q_DECL_OVERRIDE;
  
  // Is an image currently being loaded?
  virtual bool isLoading() const Q_DECL_OVERRIDE;
  virtual bool isLoadingDoubleBuffer() const Q_DECL_OVERRIDE;

  // Overload from playlistItem. Save the playlist item to playlist.
  virtual void savePlaylist(QDomElement &root, const QDir &playlistDir) const Q_DECL_OVERRIDE;
  // Create a new playlistItemOverlay from the playlist file entry. Return nullptr if parsing failed.
  static playlistItemOverlay *newPlaylistItemOverlay(const QDomElementYUView &stringElement, const QString &filePath);

  virtual ValuePairListSets getPixelValues(const QPoint &pixelPos, int frameIdx) Q_DECL_OVERRIDE;

protected slots:
  void controlChanged(int idx);
  void childChanged(bool redraw, recacheIndicator recache) Q_DECL_OVERRIDE;

private:

  // Overload from playlistItem. Create a properties widget custom to the playlistItemOverlay
  // and set propertiesWidget to point to it.
  virtual void createPropertiesWidget() Q_DECL_OVERRIDE;

  SafeUi<Ui::playlistItemOverlay_Widget> ui;

  int alignmentMode;
  QPoint manualAlignment;

  // The layout of the child items
  QRect boundingRect;
  QList<QRect> childItems;

  // Update the child item layout and this item's bounding QRect. If checkNumber is true the values
  // will be updated only if the number of items in childItems and childCount() disagree (if new items
  // were added to the overlay)
  void updateLayout(bool checkNumber=true);

  QSpacerItem *vSpacer;
};

#endif // PLAYLISTITEMOVERLAY_H
