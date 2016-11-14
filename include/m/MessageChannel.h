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
        MessageChannel& operator=(const MessageChannel&) = delete;

        template <typename MessageType, typename MessageHandler>
        Subscription subscribe(MessageHandler&& handler);

        template <typename MessageType>
        void publish(const MessageType& message);

    private:
        struct ReceiverBase {};
        template <typename MessageType> struct Receiver;
        struct ReceiverDeleter;
        using ReceiverMap = std::unordered_multimap<std::type_index, ReceiverBase*>;

        std::shared_ptr<ReceiverMap> mReceivers = std::make_shared<ReceiverMap>();
    };

    class MessageChannel::Subscription {
    public:
        Subscription(const Subscription&) = delete;
        Subscription& operator=(const Subscription&) = delete;

        void unsubscribe() { mReceiver.reset(); }

    private:
        friend MessageChannel;
        Subscription(std::shared_ptr<ReceiverBase> r) : mReceiver{std::move(r)} {}

        std::shared_ptr<ReceiverBase> mReceiver;
    };

    template <typename MessageType>
    struct MessageChannel::Receiver : public MessageChannel::ReceiverBase {
        Receiver(std::function<void(const MessageType&)> h) : handler(std::move(h)) {}
        std::function<void(const MessageType&)> handler;
    };

    struct MessageChannel::ReceiverDeleter {
        ReceiverDeleter(std::weak_ptr<ReceiverMap> subscriptions) : subscriptions(std::move(subscriptions)) {}

        template <typename MessageType>
        void operator()(Receiver<MessageType>* receiver) {
            auto map = subscriptions.lock();
            if(map) map->erase(iterator);
            delete receiver;
        }

        std::weak_ptr<ReceiverMap>  subscriptions;
        ReceiverMap::const_iterator iterator;
    };

    template <typename MessageType, typename MessageHandler>
    MessageChannel::Subscription MessageChannel::subscribe(MessageHandler&& handler) {
        auto receiver = std::shared_ptr<ReceiverBase>{new Receiver<MessageType>{std::forward<MessageHandler>(handler)}, ReceiverDeleter{mReceivers}};
        std::get_deleter<ReceiverDeleter>(receiver)->iterator = mReceivers->emplace(std::type_index{typeid(MessageType)}, receiver.get());
        return Subscription{std::move(receiver)};
    }

    template <typename MessageType>
    void MessageChannel::publish(const MessageType& message) {
        const auto range = mReceivers->equal_range(std::type_index{typeid(MessageType)});

        for (auto i = range.first; i != range.second; ++i)
            static_cast<Receiver<MessageType>*>(i->second)->handler(message);
    }
}
