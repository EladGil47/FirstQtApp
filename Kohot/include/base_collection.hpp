#ifndef BASE_COLLECTION_HPP
#define BASE_COLLECTION_HPP

#include <iostream>
#include <vector>
#include <memory>

template <typename T>
class BaseCollection
{
    protected:
        std::vector<std::shared_ptr<T>> m_collection;

    public:
        const std::vector<std::shared_ptr<T>> getCollection()
        {
            return m_collection;
        }

        std::vector<std::shared_ptr<T>>& getCollectionRef()
        {
            return m_collection;
        }

        void addItem(std::shared_ptr<T> item) 
        {
            m_collection.push_back(item);
        }

        void deleteItem(size_t index) 
        {
            if (index >= 0 && index < m_collection.size()) {
                m_collection.erase(m_collection.begin() + index);
            }
            else {
                throw std::out_of_range("Invalid index. The vector does not have an element at index " + index);
            }
        }

        size_t getSize() 
        {
            return m_collection.size();
        }

        std::shared_ptr<T> getItem(size_t index)
        {
            return m_collection[index];
        }

        virtual void display() = 0;
        virtual void createItem()
        {
            return;
        }

};

#endif // BASE_COLLECTION_HPP