
// Copyright (c) 2011 CNRS
// Authors: Florent Lamiraux


// This file is part of roboptim-core-plugin-cminpack
// roboptim-core-plugin-cminpack is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.

// roboptim-core-plugin-cminpack is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// roboptim-core-plugin-cminpack  If not, see
// <http://www.gnu.org/licenses/>.

#ifndef ROBOPTIM_CORE_SUM_OF_C1_SQUARES_HH
# define ROBOPTIM_CORE_SUM_OF_C1_SQUARES_HH

# include <boost/shared_ptr.hpp>

# include <roboptim/core/derivable-function.hh>
# include <roboptim/core/function.hh>

namespace roboptim {
  namespace cminpack {
    /// \brief Sum of the squares of differentiable functions
    ///
    /// This types enables roboptim to handle Levenberg Marquardt algorithm.
    /// This algorithm indeed minimizes the sum of squares of differentiable
    /// functions.
    ///
    /// The differentiable functions are stored in a vector valued function
    /// called base function.
    class SumOfC1Squares : public DerivableFunction
    {
    public:
      /// @name Types
      /// @{
      /// \brief Parent type
      typedef DerivableFunction parent_t;
      typedef parent_t::argument_t argument_t;
      typedef parent_t::jacobian_t jacobian_t;
      typedef parent_t::gradient_t gradient_t;
      typedef parent_t::jacobianSize_t jacobianSize_t;
      typedef Function::size_type size_t;
      typedef Function::value_type value_t;
      /// @}
      /// \brief Constructot by vector valued functions
      /// The value of this scalar valued function is the sum of the
      /// squares of the coordinates of the vector valued base function.
      explicit SumOfC1Squares (const boost::shared_ptr<DerivableFunction>&
			       function,
			       const std::string& name) throw ();
      explicit SumOfC1Squares (const SumOfC1Squares& function) throw ();
      virtual ~SumOfC1Squares () throw ();
      /// \brief Get base function
      /// Base function is the vector valued function given at construction
      /// of this class.
      const boost::shared_ptr<const DerivableFunction>& baseFunction () const;
    protected:
      /// \brief Compute value of function
      /// Value is sum of squares of coordinates of vector valued base function
      virtual void
      impl_compute(result_t &result, const argument_t &x) const throw ();
      /// \brief Gradient
      virtual void
      impl_gradient(gradient_t& gradient, const argument_t& x,
		    size_type row = 0) const throw ();
    private:
      /// Compute base function and store result in value_.
      void computeFunction (const argument_t x) const;
      /// \brief Vector valued function given at construction
      boost::shared_ptr<const DerivableFunction> baseFunction_;
      /// \brief Store last argument for which the function has been computed
      mutable argument_t x_;
      /// \brief temporary variable to store vector value of input function
      mutable result_t value_;
      /// \brief temporary variable to store gradients
      mutable gradient_t gradient_;
    }; // class Solver
  } // namespace cminpack
} // namespace roboptim
#endif // ROBOPTIM_CORE_SUM_OF_C1_SQUARES_HH
