// PriorityItem is class that stores value and its priority. We will fill Priority Queues with it
template <typename Type>
class PriorityItem
{
public:
    Type value;
    int priority;

    // Item constructor
    PriorityItem(Type v, int p) : value(v), priority(p) {}

    // Comparison operators
    bool operator>(const PriorityItem& other_item) const
    {
        return priority > other_item.priority;
    }

    bool operator<(const PriorityItem& other_item) const
    {
        return priority < other_item.priority;
    }

    bool operator==(const PriorityItem& other_item) const
    {
        return priority == other_item.priority;
    }
};
