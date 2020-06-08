
#include <atomic>

template<typename T>
class lock_free_stack
{
private:
    struct node
    {
        node * next;
	T data;

	node(T const& data_):
		data(data_)
	{}
    };

    std::atomic<node*> head;

public:
    void push(T const& data)
    {
        node * new_node = new node(data);
	new_node->next = head.load();
	while(!head.compare_exchange_weak(new_node->next, new_node));
    }

};
