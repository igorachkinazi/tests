
class Employee {
	String name;
	int payrate;
	int pay;
	public Employee(String name, int payrate) {
		this.name = name;
		this.payrate = payrate;
		pay = payrate;
	}
	String getPay() { return "$" + pay; }
	String getName() { return name; }
}

class Commission extends Employee {
	int commission;
	public Commission(String name, int payrate) {
		super(name, payrate);
		commission = 0;
	}
	public void addCommission(int commission) {
		this.commission = this.commission + commission;
		pay = payrate + this.commission;
	}
}


public class salary
{
    public static void main(String[] args)
    {
	    Employee guy1 = new Employee("Mr. Hatcher", 100000);
	    Commission guy2 = new Commission("Ms. Xie", 50000);
	    guy2.addCommission(25000);
	    System.out.println(guy1.getName() + " " + guy1.getPay());
	    System.out.println(guy2.getName() + " " + guy2.getPay());
    }
}



