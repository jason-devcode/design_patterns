
class Bundle
{
};

class Activity
{
public:
    ~Activity() = default;

protected:
    // methods to handle activity lifecycle
    virtual void onCreate() = 0;
    virtual void onStart() = 0;
    virtual void onResume() = 0;
    virtual void onPause() = 0;
    virtual void onStop() = 0;
    virtual void onClose() = 0;
    virtual void onDestroy() = 0;

    // methods to handle activity states
    virtual void onSavedInstanceState(Bundle outState) = 0;
    virtual void onRestoreInstanceState(Bundle savedInstanceState) = 0;

    // method to handle custom events
    virtual void
    onEvent(int eventId) = 0;

    // method for finish the activity
    virtual void finish() = 0;
};

int main()
{
}
