#pragma once

#include <type_traits>

#include <liborm/entity.hpp>

namespace liborm::repository {

    template <typename T>
    concept TEntity = std::is_base_of<Entity, T>();

    template <TEntity T>
    static std::vector<T> find();
    template <TEntity T>
    static std::optional<T> find(const QUuid& id);

    void save(Entity& entity);
    void remove(Entity& entity);

}  // namespace liborm::repository

#include <liborm/repository.hxx>
