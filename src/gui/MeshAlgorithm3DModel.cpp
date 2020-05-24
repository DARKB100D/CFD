#include "MeshAlgorithm3DModel.h"

MeshAlgorithm3DModel::MeshAlgorithm3DModel(QObject *parent) : QAbstractListModel(parent)
{
	m_content << qMakePair(DataPair::first_type("Delaunay"), DataPair::second_type(1))
		<< qMakePair(DataPair::first_type("Frontal"), DataPair::second_type(4));
		//<< qMakePair(DataPair::first_type("MMG3D (experimental)"), DataPair::second_type(7))
		//<< qMakePair(DataPair::first_type("R - tree (experimental)"), DataPair::second_type(9))
		//<< qMakePair(DataPair::first_type("HXT (experimental)"), DataPair::second_type(10));
}

QVariant MeshAlgorithm3DModel::data( const QModelIndex &index, int role ) const
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

int MeshAlgorithm3DModel::rowCount(const QModelIndex &/*parent*/) const
{
	return m_content.count();
}
