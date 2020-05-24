#include "MeshRecombinationAlgorithm.h"

MeshRecombinationAlgorithm::MeshRecombinationAlgorithm(QObject *parent) : QAbstractListModel(parent)
{
	m_content << qMakePair(DataPair::first_type("Simple"), DataPair::second_type(0))
		<< qMakePair(DataPair::first_type("Blossom"), DataPair::second_type(1))
		<< qMakePair(DataPair::first_type("Simple Full-Quad"), DataPair::second_type(2))
		<< qMakePair(DataPair::first_type("Blossom Full-Quad"), DataPair::second_type(3));
}

QVariant MeshRecombinationAlgorithm::data( const QModelIndex &index, int role ) const
{
	const DataPair& data = m_content.at( index.row() );
	QVariant value;

	switch (role)
	{
		case Qt::DisplayRole:
		{
			value = data.first;
		}
		break;

		case Qt::UserRole:
		{
			value = data.second;
		}
		break;

		default:
			break;
	}

	return value;
}

int MeshRecombinationAlgorithm::rowCount(const QModelIndex &/*parent*/) const
{
	return m_content.count();
}
