//
//  main.cpp
//  firstproject(akaVS)
//
//  Created by mac on 15/02/2019.
//  Copyright © 2019 mac. All rights reserved.
//
#include "header.h"


int main() {
	Vector2 v1(0,0);
	Vector2 v2(0,0);
	cin >> v1 >> v2;
	int c;
    cout << "Len v1 " << v1.Len() << " is sqrt from " << v1.sqrtLen() << endl;
	cout << "Len v2 " << v2.Len() << " is sqrt from " << v2.sqrtLen() << endl;
	cout << "v1 is: " << v1 << " v2 is: " << v2 << endl;
	cout << "their sum is: " << (v1 + v2) << endl;
	cout << "their difference is: " << v1-v2 << endl;
	cout << "v1+=v2 = " << (v1 += v2) << endl;
	cout << "v1-=v2 = " << (v1 -= v2) << endl;
	cout << "v1 and v2 is: " << v1 << v2 << endl;
	cout << "their ^ is: " << (v1^v2) << endl;
	cout << "their * is: " << v1*v2 << endl;
	cout << "Enter the const..." << endl;
	cin >> c;
	cout << "v1 * c is: " << v1*c << " and one more time: " << (c*v1) << endl;
	cout << "v2 * c is: " << v2*c << " and one more time: " << (c*v2) << endl;
	cout << "v1 / c is: " << (v1/c) << endl;
	cout << "v2 / c is: " << (v2/c) << endl;
	cout << "v1 norm is: " << v1.norm() << endl;
	cout << "v2 norm is: " << v2.norm() << endl;
	cout << "v1 perp is: " << v2.perp() << endl;
	cout << "v2 perp is: " << v2.perp() << endl;
	cout << "-v1 is: " << -v1 << endl;
	cout << "-v2 is: " << -v2 << endl;
	cout << "Enter the angle..." << endl;
	cin >> c;
	cout << "Rotate v1 is: " << v1.rotate(c) << " and " << v2.Getrotated(c) << endl;
	cout << "Rotate v2 is: " << v2.rotate(c) << " and " << v2.Getrotated(c) << endl;
	cout << "v1 and v2 is: " << v1 << v2 << endl;
    return 0;
}

