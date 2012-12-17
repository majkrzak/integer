#pragma once
//     Simple C++ binding of GNU Multiple Precision Arithmetic Library Integers.
//     Copyright (C) 2012  Piotr Majkrzak <petrol.91@gmail.com>
// 
//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
// 
//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
// 
//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include <gmp.h>
#include <string>
#include <fstream>

class Integer
{
	private:
		mpz_t value;
	public:
		Integer()
		{
			mpz_init ( *this );
		}
	public:
		Integer ( long value ) : Integer()
		{
			mpz_set_si ( *this , value );
		}
	public:
		Integer ( const std::string & value ) : Integer ()
		{
			mpz_set_str ( *this , value.c_str(), 62 );
		}
		operator std::string() const
		{
			char ret[mpz_sizeinbase ( *this, 62 ) + 2] ;
			mpz_get_str ( ret, 62, *this ) ;
			return std::string ( ret );
		}
	public:
		Integer ( mpz_srcptr value ) : Integer()
		{
			mpz_set ( *this , value );
		}
		operator mpz_ptr()
		{
			return value;
		}
		operator mpz_srcptr() const
		{
			return value;
		}
	public:
		Integer ( const Integer & rhs ) : Integer()
		{
			mpz_set ( *this , rhs );
		}
		Integer & operator= ( const Integer & rhs )
		{
			mpz_set ( *this , rhs );
		}
		Integer ( Integer && rhs ) : Integer()
		{
			mpz_swap ( *this, rhs );
		}
		Integer & operator= ( Integer && rhs )
		{
			mpz_swap ( *this, rhs );
		}
	public:
		~Integer()
		{
			mpz_clear ( *this );
		}
	public:
		friend Integer operator+ ( const Integer& lhs, const Integer& rhs )
		{
			Integer ret;
			mpz_add ( ret, lhs, rhs );
			return ret;
		}
		friend Integer operator- ( const Integer& lhs, const Integer& rhs )
		{
			Integer ret;
			mpz_sub ( ret, lhs, rhs );
			return ret;
		}
		friend Integer operator* ( const Integer& lhs, const Integer& rhs )
		{
			Integer ret;
			mpz_mul ( ret, lhs, rhs );
			return ret;
		}
		friend Integer operator/ ( const Integer& lhs, const Integer& rhs )
		{
			Integer ret;
			mpz_div ( ret, lhs, rhs );
			return ret;
		}
		friend Integer operator% ( const Integer& lhs, const Integer& rhs )
		{
			Integer ret;
			mpz_mod ( ret, lhs, rhs );
			return ret;
		}
	public:
		friend Integer& operator+= ( Integer& lhs, const Integer& rhs )
		{
			mpz_add ( lhs, lhs, rhs );
			return lhs;
		}
		friend Integer& operator-= ( Integer& lhs, const Integer& rhs )
		{
			mpz_sub ( lhs, lhs, rhs );
			return lhs;
		}
		friend Integer& operator*= ( Integer& lhs, const Integer& rhs )
		{
			mpz_mul ( lhs, lhs, rhs );
			return lhs;
		}
		friend Integer& operator/= ( Integer& lhs, const Integer& rhs )
		{
			mpz_div ( lhs, lhs, rhs );
			return lhs;
		}
		friend Integer& operator%= ( Integer& lhs, const Integer& rhs )
		{
			mpz_mod ( lhs, lhs, rhs );
			return lhs;
		}
	public:
		friend Integer operator+ ( const Integer & rhs )
		{
			return rhs;
		}
		friend Integer operator- ( const Integer & rhs )
		{
			return ( -1 ) * rhs;
		}
		friend Integer operator++ ( Integer& lhs, int )
		{
			Integer ret = lhs;
			++lhs;
			return ret;
		}
		friend Integer operator-- ( Integer& lhs, int )
		{
			Integer ret = lhs;
			--lhs;
			return ret;
		}
		friend Integer& operator++ ( Integer& rhs )
		{
			return rhs += 1;
		}
		friend Integer& operator-- ( Integer& rhs )
		{
			return rhs -= 1;
		}
	public:
		explicit operator bool() const
		{
			return mpz_sgn ( this->value ) == 0;
		}
		friend bool operator== ( const Integer& lhs, const Integer& rhs )
		{
			return mpz_cmp ( lhs, rhs ) == 0;
		}
		friend bool operator!= ( const Integer& lhs, const Integer& rhs )
		{
			return mpz_cmp ( lhs, rhs ) != 0;
		}
		friend bool operator< ( const Integer& lhs, const Integer& rhs )
		{
			return mpz_cmp ( lhs, rhs ) < 0;
		}
		friend bool operator> ( const Integer& lhs, const Integer& rhs )
		{
			return mpz_cmp ( lhs, rhs ) > 0;
		}
		friend bool operator<= ( const Integer& lhs, const Integer& rhs )
		{
			return mpz_cmp ( lhs, rhs ) <= 0;
		}
		friend bool operator>= ( const Integer& lhs, const Integer& rhs )
		{
			return mpz_cmp ( lhs, rhs ) >= 0;
		}
	public:
		template < typename mpz_function_type, typename ... mpz_function_args_type >
		Integer& call ( mpz_function_type mpz_function, mpz_function_args_type ... mpz_function_args )
		{
			mpz_function ( *this, mpz_function_args... );
		}
		template < typename mpz_function_type, typename ... mpz_function_args_type >
		static Integer Call ( mpz_function_type mpz_function, mpz_function_args_type ... mpz_function_args )
		{
			Integer ret;
			ret.call ( mpz_function, mpz_function_args... );
			return ret;
		}
	public:
		static Integer Random ( const Integer& left, const Integer& right )
		{
			static class RandomNumberGeneratorType
			{
				private:
					gmp_randstate_t state;
				public:
					RandomNumberGeneratorType()
					{
						gmp_randinit_default ( state );
						char data[4096];
						std::fstream ( "/dev/urandom", std::fstream::binary | std::fstream::in ).read ( data, 4096 );
						mpz_t seed;
						mpz_init ( seed );
						mpz_import ( seed, 4096, 1, 1, 0, 0, data );
						gmp_randseed ( state, seed );
						mpz_clear ( seed );
					}
					~RandomNumberGeneratorType()
					{
						gmp_randclear ( state );
					}
					Integer operator() ( const Integer& max )
					{
						Integer ret;
						mpz_urandomm ( ret, state, max );
						return ret;
					}
			} RandomNumberGenerator;
			return left + RandomNumberGenerator ( right - left );
		}
		static Integer NextPrime ( const Integer & integer )
		{
			Integer ret;
			mpz_nextprime ( ret, integer );
			return ret;
		}
};

