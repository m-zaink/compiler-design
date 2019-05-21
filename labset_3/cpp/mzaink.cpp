//Author : m-zaink
//Program : Producer Consumer problem using semaphores


#include <bits/stdc++.h>

// Question : 
// write a program to implement producer-consumer problem using semaphores.

//**PS : FIND SAMPLE OUTPUT AFFIXED AT THE END OF THIS FILE.

using namespace std;

typedef bool semaphore;

class Message
{
    //Class to hold the shared memory buffer.

  private:
    //semaphore to gain access to buffer.
    semaphore empty;
    //buffer as a shared memory between consumer and producer.
    string buffer;

  public:
    Message()
    {
        //Initially buffer is empty and thus empty = true;
        empty = true;
    }

    string read()
    {
        //Function to read the contents of the shared memory(buffer)
        //and subsequently empty the buffer.
        //This also sets empty = true.

        if (empty)
            return "empty";
        empty = true;
        return buffer;
    }

    void write(string item)
    {
        //Function to write onto the shared memory(buffer)
        //and subsequently set empty = false.

        if (!empty)
            return;
        buffer = item;
        empty = false;
    }
};

class Producer
{
  private:
    //var to keep track of the current message to write onto the
    //shared buffer.
    int i;

    //var to hold the pointer to shared Message object.
    Message *message;

    //vector of strings to write onto the shared buffer.
    vector<string> stringList;

  public:
    Producer(Message &message)
    {
        i = 0;
        this->message = &message;
        stringList.push_back("Humpty dumpty.");
        stringList.push_back("Sat on a wall.");
        stringList.push_back("Humpty had a great fall.");
        stringList.push_back("EOF");
    }

    void runProducer()
    {
        //Function to simulate the Producer functionality.
        cout << "MESSAGE SENT : " << stringList[i] << endl;
        message->write(stringList[i]);
        ++i;
    }
};

class Consumer
{
  private:
    //var to hold pointer to the shared Message object.
    Message *message;

    //var to hold the current message read from the shared buffer.
    string messageRead;

  public:
    Consumer(Message &message)
    {
        this->message = &message;
    }

    void runConsumer()
    {
        //Function to simulate the Consumer functionality.
        messageRead = message->read();
        if (messageRead == "empty")
            return;
        if (messageRead == "EOF")
            exit(0);

        cout << "\tMESSAGE READ : " << messageRead << endl;
    }
};

int main()
{
    Message message = Message();
    Producer producer = Producer(message);
    Consumer consumer = Consumer(message);

    for (int i = 0;; ++i)
    {
        //An infinite loop wherein the calls to producer.runProducer()
        //and consumer.runConsumer() are alternated.
        if (i % 2 == 0)
            producer.runProducer();
        else
            consumer.runConsumer();
    }
    return 0;
}

//Sample Output :
/*
    MESSAGE SENT : Humpty dumpty.
            MESSAGE READ : Humpty dumpty.
    MESSAGE SENT : Sat on a wall.
            MESSAGE READ : Sat on a wall.
    MESSAGE SENT : Humpty had a great fall.
            MESSAGE READ : Humpty had a great fall.
    MESSAGE SENT : EOF
*/