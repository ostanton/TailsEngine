#ifndef TAILS_LAYERSUBSYSTEM_HPP
#define TAILS_LAYERSUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Subsystems/Subsystem.hpp>
#include <Tails/Debug.hpp>

#include <SFML/System/Vector2.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class Layer;

    /**
     * Manages layers and their "z order"ing.
     */
    class TAILS_API LayerSubsystem final : public Subsystem
    {
    public:
        LayerSubsystem();
        ~LayerSubsystem() override;

        template<typename T>
        T* addLayer(int zOrder = 0)
        {
            static_assert(std::is_base_of_v<Layer, T>, "Failed to add layer, it does not derive Layer.");
            auto result = std::make_unique<T>();
            result->outer = this;
            result->create();
            return static_cast<T*>(addLayer(std::move(result), zOrder));
        }

        Layer* addLayer(std::unique_ptr<Layer> layer, int zOrder = 0);

        /**
         * This function doesn't immediately sort the layers. It just sets a boolean to true so at the start
         * of next frame (in preTick) the layers are sorted.
         */
        void sortLayers();

        /**
         * Gets the first layer of the specified type
         * @tparam T Layer type
         * @return Found layer or nullptr if none were found
         */
        template<typename T>
        [[nodiscard]] T* getLayerOfType()
        {
            for (auto& layer : m_layers)
                if (auto castedLayer = dynamic_cast<T*>(layer.get()))
                    return castedLayer;

            return nullptr;
        }

        /**
         * Gets the first found layer at the specified Z Order
         * @param zOrder Layer Z Order
         * @return Found layer or nullptr if not found
         */
        [[nodiscard]] Layer* getLayerOfZOrder(size_t zOrder);

        /**
         * Removes the specified layer if found
         * @param layer Layer to remove
         */
        void removeLayer(Layer* layer);

        /**
         * Removes the first found layer of the specified type
         * @tparam T Layer type
         */
        template<typename T>
        void removeLayerOfType()
        {
            for (auto& layer : m_layers)
                if (dynamic_cast<T*>(layer.get()))
                {
                    removeLayer(layer.get());
                    return;
                }
        }

        /**
         * Removes all found layers of specified type
         * @tparam T Layer type
         */
        template<typename T>
        void removeAllLayersOfType()
        {
            for (auto& layer : m_layers)
                if (dynamic_cast<T*>(layer.get()))
                    removeLayer(layer.get());
        }

    private:
        void preTick() override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void postTick() override;

        std::vector<std::unique_ptr<Layer>> m_layers;
        bool m_sortLayers {false}; // if true, sort layers at the start of next frame
    };
}

#endif // TAILS_LAYERSUBSYSTEM_HPP
