class MinStack
{
public:
    /** initialize your data structure here. */
    MinStack()
    {
    }

    void push(int x)
    {
        mElements.push(x);
        if (mElementsMin.empty() || x < mElementsMin.top())
            mElementsMin.push(x);
        else
            mElementsMin.push(mElementsMin.top());
    }

    void pop()
    {
        mElements.pop();
        mElementsMin.pop();
    }

    int top()
    {
        return mElements.top();
    }

    int getMin()
    {
        return mElementsMin.top();
    }

private:
    std::stack<int> mElements;
    std::stack<int> mElementsMin;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */