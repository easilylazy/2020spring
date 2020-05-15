//������λ
Interface Unit(key code)
{
	attribute string code;
	attribute string name;
	attribute Struct	Addr
	{ string street,string city } address;
	attribute string telephoneNumber;
}
//����
Interface Mask(key code)
{
	attribute string code;
	attribute string price;
	attribute string spec; //���  
	attribute string type; //�ͺ�

	relationship Set<Factory> producedBy
		inverse Factory::produce;
	relationship Set<Warehouse> storedBy
		inverse Warehouse::store;
}
//�ֿ�
Interface Warehouse(key number)
{
	attribute int number;
	attribute string manager;
	attribute string capacity; //����

	relationship Set<Factory> ownedBy
		inverse Factory::own;
	relationship Set<Mask> store
		inverse Mask::storedBy;
}
//����
Interface Factory:Unit
{
	relationship Set<Mask> produce
		inverse Factory::producedBy;
	relationship Set<Warehouse> own
		inverse Factory::ownedBy;
	//������
	relationship List<Order> process
		inverse Order::processedBy;
}


//����
Interface Logistic(key code)
{
	attribute string code;
	attribute string name;
	attribute string transportationType;//��������
	attribute string deliveryRange; //���ͷ�Χ

	//���Ͷ���
	relationship List<Order> deliver
		inverse Order::deliveredBy;
}
//����λ
Interface buyerUnit:Unit
{
	//�µ�
	relationship List<Order> place
		inverse Order::placedBy;

}
//����
Interface Order(key code)
{
	attribute string code;
	attribute string generateTime; //����ʱ��
	attribute string totalPrice; //�ܼ�

	attrubute struct List
	{
		string maskCode, string price, string quantity
	} list;//�����п��ֵĶ�����Ϣ


	relationship List<buyerUnit> placedBy
		inverse Unit::place;
	relationship List<Factory> processedBy
		inverse Factory::process;
	relationship List<Logistic> deliveredBy
		inverse Logistic::deliver;
}
