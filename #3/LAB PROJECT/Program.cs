using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace lab{

	/// Ископаемое
    /// @image html mineral.jpg
	class Mineral{

		/// Вес в граммах всегда положителен
		public double Weight { get { return weight; } set { weight = Math.Abs(value); } }
		protected double weight;
		
		/// цена за грамм всегда положительна
		public double Cost { get { return cost; } set { cost = Math.Abs(value); } }
		protected double cost;

		/// Конструктор устанавливает вес (weight) и цену (cost) в 0
		public Mineral(){
			weight = 0;
			cost = 0;
		}
		/** 
		 * Конструктор устанавливает вес и цену
		 * @param Weight - Вес в граммах всегда положителен
		 * @param Cost - цена за грамм всегда положительна
		 */
		public Mineral(double Weight=0.0, double Cost=0.0){
			this.Init(Weight, Cost);
		}
		
		/** 
		 * устанавливает вес и цену
		 * @param Weight - Вес в граммах всегда положителен
		 * @param Cost - цена за грамм всегда положительна
		 */
		public void Init(double Weight=0.0, double Cost=0.0){
			weight = Math.Abs(Weight);
			cost = Math.Abs(Cost);
		}

		/// выводит содержимое класса
		public void Display(){
			Console.WriteLine(this);
		}

		/// производит чтение данных из консоли
		public virtual void Read(){
			while(true){
				Console.Write("Введите вес ископаемого (г): ");
				string tmp = Console.ReadLine();
				double tmp_weight;
				if(Double.TryParse(tmp, out tmp_weight)){
					Weight = tmp_weight;
					break;
				}
			}

			while(true){
				Console.Write("Введите стоимость ископаемого (р/г): ");
				string tmp = Console.ReadLine();
				double tmp_cost;
				if(Double.TryParse(tmp, out tmp_cost)){
					Cost = tmp_cost;
					break;
				}
			}
		}

		/**
		 * общая стоимость
		 * @f$ weight * cost @f$
		 * @return Стоимость ископаемого
		 */
		public virtual double Price(){
			return weight * cost;
		}

		/**
		 * @return строку с данными ископаемого (вес, цена, общая стоимость)
		 */
		public override string ToString(){
			return "Вес ископаемого: " + weight + " г\r\nСтоимость икопаемого: " + cost + " р/г\r\nОбщая стоимость икопаемого: " + this.Price() + " р";
		}

	}

	/// Минерал с примесями
    /// @image html impurity_mineral.jpg
	class ImpurityMineral : Mineral{
		/// % примесей от 0 до 1
		public double Impurity { get { return impurity; } set { impurity = Math.Abs(value); if(impurity > 1)impurity = 1; } }
		private double impurity;
		

		/// устанавливает цену, вес и % примесей в 0
		public ImpurityMineral() : base(){
			impurity = 0;
		}
		/**
		 * устанавливает вес, цену и % примесей
		 * @param Weight - Вес в граммах всегда положителен
		 * @param Cost - цена за грамм всегда положительна
		 * @param Impurity - % примесей от 0 до 1
		 */
		public ImpurityMineral(double Weight=0.0, double Cost=0.0, double Impurity = 0.0){
			this.Init(Weight, Cost, Impurity);
		}
		
		/**
		 * устанавливает вес, цену и % примесей
		 * @param Weight - Вес в граммах всегда положителен
		 * @param Cost - цена за грамм всегда положительна
		 * @param Impurity - % примесей от 0 до 1
		 */
		public void Init(double Weight=0.0, double Cost=0.0, double Impurity = 0.0){
			base.Init(Weight, Cost);
			impurity = Math.Abs(Impurity);
			if(impurity > 1)
				impurity = 1;
		}
		
		/// производит чтение данных из консоли
		public override void Read(){
			base.Read();
			while(true){
				Console.Write("Введите количество примесей (%, 0-1): ");
				string tmp = Console.ReadLine();
				double tmp_impurity;
				if(Double.TryParse(tmp, out tmp_impurity)){
					Impurity = tmp_impurity;
					break;
				}
			}
		}

		
		/**
		 * общая стоимость минус стоимость примесей
		 * @f$ (weight * cost) * (1 - impurity) @f$
		 * @return Стоимость ископаемого
		 */
		public override double Price(){
			return weight * cost * (1-impurity);
		}

		/**
		 * @return строку с данными ископаемого (вес, цена, общая стоимость, % примесей)
		 */
		public override string ToString(){
			return base.ToString() + "\r\nКоличество примесей: " + (Impurity*100) + "%";
		}
	}

	/// Раскопки
	abstract class Excavations{

		/// Стоимость проведения раскопок всегда положительная
		public double Expenses {get { return expenses; } set { expenses = Math.Abs(value); }}
		protected double expenses;

		/**
		 * устанавливает стоимость проведения раскопок в 0
		 */
		public Excavations(){
			expenses = 0.0;
		}

		/**
		 * устанавливает стоимость проведения раскопок в 0
		 * @param Expenses - Стоимость проведения раскопок
		 */
		public virtual void Init(double Expenses = 0.0){
			expenses = Math.Abs(Expenses);
		}
		
		/// производит чтение данных из консоли
		public virtual void Read(){
			while(true){
				Console.Write("Введите стоимость раскопок (р): ");
				string tmp = Console.ReadLine();
				double tmp_;
				if(Double.TryParse(tmp, out tmp_)){
					Expenses = tmp_;
					break;
				}
			}
		}

		/**
		 * вызывает метод Read() у переданного ископаемого
		 * @see Mineral::Read()
		 * @param Mineral
		 */
		protected void ReadMineral(Mineral Mineral){
			Mineral.Read();
		}

		/// выводит содержимое класса
		public virtual void Display(){
			Console.WriteLine("Стоимость раскопок: "+expenses);
			Console.WriteLine("Прибыль раскопок: "+ExcavationsCost());
			Console.WriteLine("Самое ценное ископаемое: "+MostValuableMineral());
		}

		/// @return прибыль раскопок
		public virtual double ExcavationsCost(){
			return -expenses;
		}

		/// @return номер самого дорого ископаемого
		public abstract int MostValuableMineral();
	}

	/// раскопки добывшие 3 ископаемого
	class ThreeMineralsExcavations : Excavations{
		/// ископаемое #1
		public Mineral mineral_1 {get; private set;}
		/// ископаемое #2
		public Mineral mineral_2 {get; private set;}
		/// ископаемое #3
		public Mineral mineral_3 {get; private set;}

		/// производит установку стоимости раскопок в 0 и сохздает экземпляры ископаемых
		public ThreeMineralsExcavations() : base(){
			mineral_1 = new Mineral();
			mineral_2 = new Mineral();
			mineral_3 = new Mineral();
		}
		
		/// производит установку стоимости раскопок
		/// @param Expenses - стоимость проведения раскопок всегда положительная
		public override void Init(double Expenses = 0.0){
			base.Init(Expenses);
		}

		/// производит чтение данных из консоли
		public override void Read(){
			base.Read();

			Console.WriteLine("Ископаемое 1:");
			ReadMineral(mineral_1);
			Console.WriteLine("Ископаемое 2:");
			ReadMineral(mineral_2);
			Console.WriteLine("Ископаемое 3:");
			ReadMineral(mineral_3);
		}

		/// производит вывод содержимого
		public override void Display(){
			base.Display();
			Console.WriteLine("Ископаемое 1:");
			mineral_1.Display();
			Console.WriteLine("Ископаемое 2:");
			mineral_2.Display();
			Console.WriteLine("Ископаемое 3:");
			mineral_3.Display();
		}

		/// @return прибыль раскопок (стоимость ископаемых - стоимость раскопок)
		/// @see Mineral::Price()
		public override double ExcavationsCost(){
			return mineral_1.Price() + mineral_2.Price() + mineral_3.Price() - expenses;
		}

		/**
		 * @return номер самого дорого ископаемого
		 */
		public override int MostValuableMineral(){
			double price_1 = mineral_1.Price();
			double price_2 = mineral_2.Price();
			double price_3 = mineral_3.Price();
			return (price_1 > price_2 ? (price_1 > price_3 ? 1 : 3) : (price_2 > price_3 ? 2 : 3));
		}
	}

	/// раскопки добывшие обычное ископаемое и ископаемое с примесями
	class MineralImpurityMineralExcavations : Excavations{
		/// обычное ископаемое
		public Mineral mineral {get; private set;}
		/// ископаемое с примесями
		public ImpurityMineral impurity_mineral {get; private set;}
		
		/// производит установку стоимости раскопок в 0 и сохздает экземпляры ископаемых
		public MineralImpurityMineralExcavations() : base(){
			mineral = new Mineral();
			impurity_mineral = new ImpurityMineral();
		}
		
		/// производит установку стоимости раскопок
		/// @param Expenses - стоимость проведения раскопок всегда положительная
		public override void Init(double Expenses = 0.0){
			base.Init(Expenses);
		}
		
		/// производит чтение данных из консоли
		public override void Read(){
			base.Read();

			Console.WriteLine("Ископаемое:");
			ReadMineral(mineral);
			Console.WriteLine("Ископаемое с примесями:");
			ReadMineral(impurity_mineral);
		}
		
		/// производит вывод содержимого
		public override void Display(){
			base.Display();
			Console.WriteLine("Ископаемое:");
			mineral.Display();
			Console.WriteLine("Ископаемое с примесями:");
			impurity_mineral.Display();
		}
		
		/// @return прибыль раскопок (стоимость ископаемых - стоимость раскопок)
		/// @see Mineral::Price()
		public override double ExcavationsCost(){
			return mineral.Price() + impurity_mineral.Price() - expenses;
		}
		
		/**
		 * @return номер самого дорого ископаемого
		 * 1 - обычное скопаемое
		 * 2 - ископаемое с примесями
		 */
		public override int MostValuableMineral(){
			return (mineral.Price() > impurity_mineral.Price() ? 1 : 2);
		}
	}


	/// одиночка для раскпок с тремя ископаемыми
	class Singleton_ThreeMineralsExcavations : ThreeMineralsExcavations{
		/// экземпляр одиночки
		private static readonly Singleton_ThreeMineralsExcavations instance = new Singleton_ThreeMineralsExcavations();
		private Singleton_ThreeMineralsExcavations() :  base(){}

		/// экземпляр одиночки
		public static Singleton_ThreeMineralsExcavations Instance {get { return instance; } }
	}


	class Program{
		/// точка входа в приложение
		/// @param args - аргументы командной строки
		static void Main(string[] args){

			Singleton_ThreeMineralsExcavations first_excavations = Singleton_ThreeMineralsExcavations.Instance;
			
			Console.WriteLine("Первые раскопки:");
			first_excavations.Read();
			first_excavations.Display();
			Console.WriteLine("\r\n");

			Singleton_ThreeMineralsExcavations second_excavations = Singleton_ThreeMineralsExcavations.Instance;
			
			Console.WriteLine("Вторые раскопки:");
			second_excavations.Read();
			second_excavations.Display();
			Console.WriteLine("\r\n");
			
			Console.WriteLine("Первые раскопки:");
			first_excavations.Display();
			Console.WriteLine("\r\n");

			
			Console.ReadKey();
		}
	}
}
