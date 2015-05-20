#pragma once
#include <memory>
#include <unordered_map>
#include <functional>

namespace m
{
    class MessageChannel
    {
    public:
        class Subscription;

        MessageChannel();
        MessageChannel(const MessageChannel&) = delete;
        MessageChannel(MessageChannel&&) = default;
        MessageChannel& operator=(const MessageChannel&) = delete;
        MessageChannel& operator=(MessageChannel&&) = default;

        template<class MessageType, class MessageHandler>
        Subscription subscribe(MessageHandler&& handler);

        template<class MessageType>
        void publish(const MessageType& message);

    private:
        struct ReceiverBase;
        template<class MessageType> struct Receiver;
        struct ReceiverDeleter;
        using ReceiverMap = std::unordered_multimap<size_t, ReceiverBase*>;

        std::shared_ptr<ReceiverMap> mReceivers;
    };

    class MessageChannel::Subscription
    {
    public:
        Subscription(const Subscription&) = delete;
        Subscription(Subscription&&) = default;
        Subscription& operator=(const Subscription&) = delete;
        Subscription& operator=(Subscription&&) = default;

        void reset();

    private:
        Subscription(std::shared_ptr<ReceiverBase> r);

        std::shared_ptr<ReceiverBase> mReceiver;
        friend MessageChannel;
    };

    struct MessageChannel::ReceiverBase {};

    template<class MessageType>
    struct MessageChannel::Receiver : public MessageChannel::ReceiverBase
    {
        Receiver(std::function<void(const MessageType&)> h) : handler(std::move(h)) {}
        std::function<void(const MessageType&)> handler;
    };

    struct MessageChannel::ReceiverDeleter
    {
        ReceiverDeleter(std::weak_ptr<ReceiverMap> subscriptions) : subscriptions(std::move(subscriptions)) {}

        template<class MessageType>
        void operator()(Receiver<MessageType>* receiver)
        {
            auto map = subscriptions.lock();
            if(map) map->erase(iterator);
            delete receiver;
        }

        std::weak_ptr<ReceiverMap>  subscriptions;
        ReceiverMap::const_iterator iterator;
    };

    inline MessageChannel::MessageChannel() : mReceivers{std::make_shared<ReceiverMap>()} {}

    template<class MessageType, class MessageHandler>
    MessageChannel::Subscription MessageChannel::subscribe(MessageHandler&& handler)
    {
        auto receiver = std::shared_ptr<ReceiverBase>{new Receiver<MessageType>{std::forward<MessageHandler>(handler)}, ReceiverDeleter{mReceivers}};
        std::get_deleter<ReceiverDeleter>(receiver)->iterator = mReceivers->emplace(typeid(MessageType).hash_code(), receiver.get());
        return Subscription{std::move(receiver)};
    }

    template<class MessageType>
    void MessageChannel::publish(const MessageType& message)
    {
        const auto range = mReceivers->equal_range(typeid(MessageType).hash_code());

        for (auto i = range.first; i != range.second; ++i)
            static_cast<Receiver<MessageType>*>(i->second)->handler(message);
    }

    inline MessageChannel::Subscription::Subscription(std::shared_ptr<ReceiverBase> r) : mReceiver{std::move(r)} {}

    inline void MessageChannel::Subscription::reset() { mReceiver.reset(); }
}
