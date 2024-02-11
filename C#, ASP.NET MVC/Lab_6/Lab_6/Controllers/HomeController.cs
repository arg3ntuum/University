﻿using Lab_6.Models;
using Microsoft.AspNetCore.Mvc;

using Microsoft.EntityFrameworkCore;


namespace Lab_6.Controllers

{

    public class HomeController : Controller

    {

        ApplicationContext db;

        public HomeController(ApplicationContext context)

        {

            db = context;

        }
        [HttpPost]

        public async Task<IActionResult> Delete(int? id)

        {

            if (id != null)

            {

                User user = new User { Id = id.Value };

                db.Entry(user).State = EntityState.Deleted;

                await db.SaveChangesAsync();

                return RedirectToAction("Index");

            }

            return NotFound();

        }
        public async Task<IActionResult> Edit(int? id)

        {

            if (id != null)

            {

                User? user = await db.Users.FirstOrDefaultAsync(p => p.Id == id);

                if (user != null) return View(user);

            }

            return NotFound();

        }

        [HttpPost]

        public async Task<IActionResult> Edit(User user)

        {

            db.Users.Update(user);

            await db.SaveChangesAsync();

            return RedirectToAction("Index");

        }
        public async Task<IActionResult> Index()

        {

            return View(await db.Users.ToListAsync());

        }

        public IActionResult Create()

        {

            return View();

        }

        [HttpPost]

        public async Task<IActionResult> Create(User user)

        {

            db.Users.Add(user);

            await db.SaveChangesAsync();

            return RedirectToAction("Index");

        }

    }

}