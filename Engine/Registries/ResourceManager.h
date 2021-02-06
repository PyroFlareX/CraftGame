#pragma once

#include <unordered_map>
namespace vn
{
	template<typename T>
	class Registry
	{
	public:
		Registry() = default;

		void addToRegistry(T res, const int& id)
		{
			m_registry.insert({ id, res });
		}

		T& getAsset(const int& id)
		{
			return m_registry.find(id)->second;
		}

		~Registry() = default;
	private:
		std::unordered_map<int, T> m_registry;
	};
}