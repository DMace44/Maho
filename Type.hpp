#pragma once

#include <string>
#include <vector>
#include <map>

namespace parser
{
	enum class TypeDeclaration
	{
		STRUCTURE,
		CLASS,
		ENUMERATOR
	};

	struct Type
	{
	public:
		std::string m_Name{};
		std::vector<Type> m_Fields{};
		TypeDeclaration m_TypeInfo{};
	public:
		Type() = default;
		Type(std::string name, TypeDeclaration typeInfo) : m_Name(name), m_TypeInfo(typeInfo) {}
	};
}