#ifndef INETWORKSESSION_H
#define INETWORKSESSION_H

class CEvent;

class INetworkSession
{
    public:
		virtual void send(boost::shared_ptr<CEvent> event)=0;
		virtual void close()=0;

		//Point d'entre du thread (start le io_service)
		virtual void run()=0;
};

#endif // CHU_INETWORKSESSION_H
