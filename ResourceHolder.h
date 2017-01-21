/**
*
* \class ResourceHolder
*
* \brief ��������� ��������.
*
* �������� ������ (��������, �����, ����) � ���������� ID.
* ���� ����������� ��������� � �������� ������ �� ID.
*
* \author SFML | ���� ���������
*
* \copyright http://www.sfml-dev.org/
*
*/

#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	using Ptr = std::unique_ptr < Resource >;

	/// ��������� ����� ������
	/// \param id ���������� ���� �������
	/// \param filename ������������� ���� � �������
	void load(Identifier id, const std::string& filename);

	/// ��������� ����� ������
	/// \param id ���������� ���� �������
	/// \param filename ������������� ���� � �������
	/// \param secondParam �������������� �������� (��������� ��� ��������� ��������)
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);

	/// �������� ������ �� �����
	/// \param id ���� �������
	/// \return ������ �� ������
	Resource& get(Identifier id);

	/// �������� ������ �� �����
	/// \param id ���� �������
	/// \return ������ �� ������
	const Resource&	get(Identifier id) const;

private:
	/// ������� ������ � ������
	/// \param id ���� (�������������)
	/// \param resource �������� (������)
	void insertResource(Identifier id, Ptr&& resource);

private:
	/// ������ ID - ������, ���������� ��������
	std::map<Identifier, Ptr> mResourceMap;
};

#include "ResourceHolder.inl"