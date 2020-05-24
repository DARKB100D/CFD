#include "MeshSubdivisionAlgorithm.h"

MeshSubdivisionAlgorithm::MeshSubdivisionAlgorithm(QObject *parent) : QAbstractListModel(parent)
{
	m_content << qMakePair(DataPair::first_type("None"), DataPair::second_type(0))
		<< qMakePair(DataPair::first_type("All Quadrs"), DataPair::second_type(1))
		<< qMakePair(DataPair::first_type("All Hexas"), DataPair::second_type(2));
		//<< qMakePair(DataPair::first_type("Barycentric (experimental)"), DataPair::second_type(3));
}

QVariant MeshSubdivisionAlgorithm::data( const QModelIndex &index, int role ) const
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

int MeshSubdivisionAlgorithm::rowCount(const QModelIndex &/*parent*/) const
{
	return m_content.count();
}
