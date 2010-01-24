/*-
 * Copyright (c) 2009 Ander Suarez and Endika Gutiérrez
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of copyright holders nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL COPYRIGHT HOLDERS OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


/**
 *  \file Estimator.h
 *  \author Ander Suárez & Endika Gutiérrez
 *  \date 16/01/09
 */

#ifndef Estimator_h
#define Estimator_h

#include <queue>
#include "OpenCV.h"

const int ESTIMATOR_QUEUE_LENGTH = 64;

namespace OpenCV {

    namespace MachineLearning {
        /**
         *  Estimator
         *  Estimates learned Pattern.
         *  Template for each Model.
         */
        template <class t_statModel>
        class Estimator {
        public:
        // Constructors
            Estimator();
            Estimator(const Estimator&);
            virtual ~Estimator();
    
        // Public Methods
            /**
             *  Trains stimator with Value
             *  \param  [in]    value   Value to learn.
             */
            void train(double);
            /**
             *  Estimates Value
             *  \return Estimated value
             */
            double predict() const;

            /// Evaluates probability of one value
            double evaluate(double) const;
    
        protected:
          CvStatModel* m_estimatorModel;  //abstract class; Use CvNormalBayesClassifier, CvKNearest or CvSVM
        };

        //Diferent types of estimators
        typedef Estimator<CvNormalBayesClassifier>  NormalBayesEstimator;
        typedef Estimator<CvKNearest>               KNearestEstimator;
        typedef Estimator<CvSVM>                    SVMEstimator;

    } // namespace MachineLearning

} // namespace OpenCV

#endif // Estimator_h
