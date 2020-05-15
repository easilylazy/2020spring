//基本单位
Interface Unit(key code)
{
	attribute string code;
	attribute string name;
	attribute Struct	Addr
	{ string street,string city } address;
	attribute string telephoneNumber;
}
//口罩
Interface Mask(key code)
{
	attribute string code;
	attribute string price;
	attribute string spec; //规格  
	attribute string type; //型号

	relationship Set<Factory> producedBy
		inverse Factory::produce;
	relationship Set<Warehouse> storedBy
		inverse Warehouse::store;
}
//仓库
Interface Warehouse(key number)
{
	attribute int number;
	attribute string manager;
	attribute string capacity; //容量

	relationship Set<Factory> ownedBy
		inverse Factory::own;
	relationship Set<Mask> store
		inverse Mask::storedBy;
}
//工厂
Interface Factory:Unit
{
	relationship Set<Mask> produce
		inverse Factory::producedBy;
	relationship Set<Warehouse> own
		inverse Factory::ownedBy;
	//处理订单
	relationship List<Order> process
		inverse Order::processedBy;
}


//物流
Interface Logistic(key code)
{
	attribute string code;
	attribute string name;
	attribute string transportationType;//运输类型
	attribute string deliveryRange; //配送范围

	//配送订单
	relationship List<Order> deliver
		inverse Order::deliveredBy;
}
//购买单位
Interface buyerUnit:Unit
{
	//下单
	relationship List<Order> place
		inverse Order::placedBy;

}
//订单
Interface Order(key code)
{
	attribute string code;
	attribute string generateTime; //生成时间
	attribute string totalPrice; //总价

	attrubute struct List
	{
		string maskCode, string price, string quantity
	} list;//订单中口罩的订购信息


	relationship List<buyerUnit> placedBy
		inverse Unit::place;
	relationship List<Factory> processedBy
		inverse Factory::process;
	relationship List<Logistic> deliveredBy
		inverse Logistic::deliver;
}
