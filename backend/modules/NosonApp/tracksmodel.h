/*
 *      Copyright (C) 2015-2016 Jean-Luc Barriere
 *
 *  This file is part of Noson-App
 *
 *  Noson-App is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Noson is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TRACKSMODEL_H
#define TRACKSMODEL_H

#include "listmodel.h"
#include "../../lib/noson/noson/src/contentdirectory.h"

#include <QAbstractListModel>

class TrackItem
{
public:
  TrackItem(const SONOS::DigitalItemPtr& ptr, const QString& baseURL);

  virtual ~TrackItem() { }

  bool isValid() const { return m_valid; }

  QVariant payload() const;

  const QString& id() const { return m_id; }

  const QString& title() const { return m_title; }

  const QString& author() const { return m_author; }

  const QString& album() const { return m_album; }

  const QString& albumTrackNo() const { return m_albumTrackNo; }

  const QString& art() const { return m_art; }

  bool isService() const { return m_isService; }

private:
  SONOS::DigitalItemPtr m_ptr;
  bool m_valid;
  QString m_id;
  QString m_title;
  QString m_author;
  QString m_album;
  QString m_albumTrackNo;
  QString m_art;
  bool m_isService;
};

class TracksModel : public QAbstractListModel, public ListModel
{
  Q_OBJECT
  Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
  Q_PROPERTY(int totalCount READ totalCount NOTIFY totalCountChanged)
  
public:
  enum TrackRoles
  {
    PayloadRole,
    IdRole,
    TitleRole,
    AuthorRole,
    AlbumRole,
    AlbumTrackNoRole,
    ArtRole,
    IsServiceRole,
  };

  TracksModel(QObject* parent = 0);
  virtual ~TracksModel();

  void addItem(TrackItem* item);

  int rowCount(const QModelIndex& parent = QModelIndex()) const;

  QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  Q_INVOKABLE QVariantMap get(int row);

  Q_INVOKABLE bool init(QObject* sonos, const QString& root, bool fill = false);

  Q_INVOKABLE void clear();

  Q_INVOKABLE bool load();

  int totalCount() const { return m_totalCount; }

  Q_INVOKABLE bool loadMore();

  Q_INVOKABLE bool asyncLoad();

  virtual void handleDataUpdate();

  Q_INVOKABLE int containerUpdateID() { return m_updateID; }

signals:
  void dataUpdated();
  void countChanged();
  void totalCountChanged();

protected:
  QHash<int, QByteArray> roleNames() const;

private:
  QList<TrackItem*> m_items;

  SONOS::ContentDirectory* m_contentDirectory;
  SONOS::ContentList* m_contentList;
  SONOS::ContentList::iterator m_iterator;
  unsigned m_totalCount;

};

#endif /* TRACKSMODEL_H */

