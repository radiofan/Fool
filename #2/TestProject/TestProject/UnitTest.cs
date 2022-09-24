using LabProject;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;

namespace TestProject {
	[TestClass]
	public class UnitTest {

		[TestMethod]
		public void fibonachchi_test_0(){
			Assert.AreEqual(0M, Program.fibonachchi(0));
		}
		[TestMethod]
		public void fibonachchi_test_1(){
			Assert.AreEqual(1M, Program.fibonachchi(1));
		}
		[TestMethod]
		public void fibonachchi_test_10(){
			Assert.AreEqual(55M, Program.fibonachchi(10));
		}
		[TestMethod]
		public void fibonachchi_test_20(){
			Assert.AreEqual(6765M, Program.fibonachchi(20));
		}
		[TestMethod]
		public void fibonachchi_test_100(){
			Assert.AreEqual(354224848179261915075M, Program.fibonachchi(100));
		}


		[TestMethod]
		public void simple_test_0(){
			decimal[] expected = new decimal[]{};
			decimal[] actual = Program.simple(0);
			Assert.AreEqual(expected.Length, actual.Length);
			for(int i=0; i<expected.Length; i++){
				Assert.AreEqual(expected[i], actual[i]);
			}
		}
		[TestMethod]
		public void simple_test_1(){
			decimal[] expected = new decimal[]{1};
			decimal[] actual = Program.simple(1);
			Assert.AreEqual(expected.Length, actual.Length);
			for(int i=0; i<expected.Length; i++){
				Assert.AreEqual(expected[i], actual[i]);
			}
		}
		[TestMethod]
		public void simple_test_20(){
			decimal[] expected = new decimal[]{1,2,3,5,7,11,13,17,19};
			decimal[] actual = Program.simple(20);
			Assert.AreEqual(expected.Length, actual.Length);
			for(int i=0; i<expected.Length; i++){
				Assert.AreEqual(expected[i], actual[i]);
			}
		}
		[TestMethod]
		public void simple_test_100(){
			decimal[] expected = new decimal[]{1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
			decimal[] actual = Program.simple(100);
			Assert.AreEqual(expected.Length, actual.Length);
			for(int i=0; i<expected.Length; i++){
				Assert.AreEqual(expected[i], actual[i]);
			}
		}


		[TestMethod]
		public void high_bit_number_0x0000000000000000(){
			Assert.AreEqual(-1, Program.high_bit_number(0x0000000000000000));
		}
		[TestMethod]
		public void high_bit_number_0x0000000000000001(){
			Assert.AreEqual(0, Program.high_bit_number(0x0000000000000001));
		}
		[TestMethod]
		public void high_bit_number_0xFFFFFFFFFFFFFFFF(){
			Assert.AreEqual(63, Program.high_bit_number(0xFFFFFFFFFFFFFFFF));
		}
		[TestMethod]
		public void high_bit_number_0x0000000000400000(){
			Assert.AreEqual(22, Program.high_bit_number(0x0000000000400000));
		}


		[TestMethod]
		public void draw_sandglass_0_0(){
			Assert.AreEqual("", Program.draw_sandglass(0,0));
		}
		[TestMethod]
		public void draw_sandglass_1_5(){
			string expected =
"*****\r\n";
			Assert.AreEqual(expected, Program.draw_sandglass(1,5));
		}
		[TestMethod]
		public void draw_sandglass_5_1(){
			string expected =
"*\r\n" +
" \r\n" +
" \r\n" +
" \r\n" +
"*\r\n";
			Assert.AreEqual(expected, Program.draw_sandglass(5,1));
		}
		[TestMethod]
		public void draw_sandglass_5_3(){
			string expected =
"***\r\n" +
" * \r\n" +
"   \r\n" +
" * \r\n" +
"***\r\n";
			Assert.AreEqual(expected, Program.draw_sandglass(5,3));
		}
		[TestMethod]
		public void draw_sandglass_5_5(){
			string expected =
"*****\r\n"+
" *** \r\n"+
"  *  \r\n"+
" *** \r\n"+
"*****\r\n";
			Assert.AreEqual(expected, Program.draw_sandglass(5,5));
		}


		[TestMethod]
		public void parent_str_abcdef_defabc(){
			Assert.AreEqual("defabcdef", Program.parent_str("abcdef","defabc"));
		}
		[TestMethod]
		public void is_palindrom_aaa(){
			Assert.AreEqual(true, Program.is_palindrom("aaa"));
		}
		[TestMethod]
		public void is_palindrom_df(){
			Assert.AreEqual(false, Program.is_palindrom("df"));
		}


		[TestMethod]
		public void palindrom_count_123456(){
			Assert.AreEqual(6, Program.palindrom_count("123456"));
		}
		[TestMethod]
		public void palindrom_count_potop(){
			Assert.AreEqual(1, Program.palindrom_count("potop"));
		}
		[TestMethod]
		public void palindrom_count_asamanam(){
			Assert.AreEqual(2, Program.palindrom_count("asamanam"));
		}

		
		[TestMethod]
		public void is_even_7(){
			Assert.AreEqual(false, Program.is_even(7));
		}
		[TestMethod]
		public void is_even_0(){
			Assert.AreEqual(true, Program.is_even(0));
		}
		[TestMethod]
		public void is_odd_7(){
			Assert.AreEqual(true, Program.is_odd(7));
		}
		[TestMethod]
		public void is_odd_0(){
			Assert.AreEqual(false, Program.is_odd(0));
		}


		[TestMethod]
		public void sign__5(){
			Assert.AreEqual(-1, Program.sign(-5));
		}
		[TestMethod]
		public void sign_20(){
			Assert.AreEqual(1, Program.sign(20));
		}
		[TestMethod]
		public void sign_0(){
			Assert.AreEqual(0, Program.sign(0));
		}
	}
}
