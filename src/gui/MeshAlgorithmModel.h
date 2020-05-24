#pragma once
#include <QAbstractListModel>

class MeshAlgorithmModel : public QAbstractListModel
{
	Q_OBJECT

	typedef QPair<QVariant, QVariant> DataPair;
	QList< DataPair > m_content;

public:
	explicit MeshAlgorithmModel( QObject *parent = 0 );
	virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const;
};
