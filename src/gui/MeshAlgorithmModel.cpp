#include "MeshAlgorithmModel.h"

MeshAlgorithmModel::MeshAlgorithmModel(QObject *parent) : QAbstractListModel(parent)
{
	m_content << qMakePair(DataPair::first_type("Mesh adapt"), DataPair::second_type(1))
		<< qMakePair(DataPair::first_type("Automatic"), DataPair::second_type(2))
		<< qMakePair(DataPair::first_type("Delaunay"), DataPair::second_type(5))
		<< qMakePair(DataPair::first_type("Frontal - Delaunay"), DataPair::second_type(6));
		//<< qMakePair(DataPair::first_type("BAMG (experimental)"), DataPair::second_type(7))
		//<< qMakePair(DataPair::first_type("Frontal - Delaunay for Quads (experimental)"), DataPair::second_type(8))
		//<< qMakePair(DataPair::first_type("Packing of Parallelograms (experimental)"), DataPair::second_type(9));
}

QVariant MeshAlgorithmModel::data( const QModelIndex &index, int role ) const
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

int MeshAlgorithmModel::rowCount(const QModelIndex &/*parent*/) const
{
	return m_content.count();
}
