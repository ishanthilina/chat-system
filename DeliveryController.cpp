
DeliveryController::DeliveryController( Logger * o_Logger, Server * o_Server )
{
	this->o_Logger=o_Logger;
	this->o_Server=o_Server;
}

int DeliveryController::processMessage( Message * o_Message )
{
	cout<<"Processing message: "<< o_Message->GetMessage();

	return 0;

}
