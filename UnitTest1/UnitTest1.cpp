#include "pch.h"
#include "CppUnitTest.h"
#include "../pds_12/pds_12.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
        TEST_METHOD(TestDijkstraShortestPath) {
            graph[0].push_back({ 1, 4 });
            graph[0].push_back({ 2, 1 });
            graph[1].push_back({ 2, 2 });
            graph[2].push_back({ 1, 5 });

            int dist[MAX_VERTICES], prev[MAX_VERTICES];
            int n = 3; 

            dijkstra(0, n, dist, prev);

            Assert::AreEqual(0, dist[0]);  
            Assert::AreEqual(4, dist[1]);  
            Assert::AreEqual(1, dist[2]);  

            Assert::AreEqual(-1, prev[0]); 
            Assert::AreEqual(0, prev[1]);  
            Assert::AreEqual(0, prev[2]);  
        }

	};
}
