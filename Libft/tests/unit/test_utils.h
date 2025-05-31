/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hozhan <hozhan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:53:16 by hozhan            #+#    #+#             */
/*   Updated: 2025/05/31 23:53:18 by hozhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# define RED   "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

# define TEST_ASSERT(expr) \
    do { \
        if (!(expr)) { \
            printf(RED "✗ Test failed at %s:%d\n" RESET, __FILE__, __LINE__); \
            return; \
        } \
    } while (0)

# define RUN_TEST(test_func) \
    do { \
        printf("Testing %-20s", #test_func); \
        test_func(); \
        printf(GREEN "✓\n" RESET); \
    } while (0)

#endif