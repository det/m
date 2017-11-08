#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <typeindex>

namespace m {
    class MessageChannel {
    public:
        class Subscription;

        MessageChannel() = default;
        MessageChannel(const MessageChannel&) = delete;
        MessageChannel(MessageChannel&&) = default;
        MessageChannel& operator=(const MessageChannel&) = delete;
        MessageChannel& operator=(MessageChannel&&) = default;

        template <class MessageType>
        Subscription subscribe(std::function<void(const MessageType&)> handler);

        template <class MessageType>
        void publish(const MessageType& message);

    private:
        using SubscriberMap = std::unordered_multimap<std::type_index, void*>;
        std::shared_ptr<SubscriberMap> mSubscriptions = std::make_shared<SubscriberMap>();
    };

    class MessageChannel::Subscription {
    public:
        Subscription(const Subscription&) = delete;
        Subscription(Subscription&&) = default;
        Subscription& operator=(const Subscription&) = delete;
        Subscription& operator=(Subscription&&) = default;

        void unsubscribe() { mReceiver.reset(); }

    private:
        friend MessageChannel;
        Subscription(std::shared_ptr<void>&& r) : mReceiver{std::move(r)} {}
        std::shared_ptr<void> mReceiver;
    };

    template <class MessageType>
    MessageChannel::Subscription MessageChannel::subscribe(std::function<void(const MessageType&)> handler) {
        auto receiver = std::make_unique<std::function<void(const MessageType&)>>(std::move(handler));
        auto deleter = [subs = std::weak_ptr<SubscriberMap>{mSubscriptions},
                        iter = mSubscriptions->emplace(std::type_index{typeid(MessageType)}, receiver.get())](auto* receiver) {
            auto p = std::unique_ptr<std::function<void(const MessageType&)>>{receiver};
            if (auto map = subs.lock())
                map->erase(iter);
        };
        return {{receiver.release(), std::move(deleter)}};
    }

    template <class MessageType>
    void MessageChannel::publish(const MessageType& message) {
        auto range = mSubscriptions->equal_range(std::type_index{typeid(MessageType)});

        for (auto i = range.first; i != range.second; ++i)
            (*static_cast<std::function<void(const MessageType&)>*>(i->second))(message);
    }
}
